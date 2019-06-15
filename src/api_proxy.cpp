//  lazyvec - R package for creating, testing and deploying custom ALTREP vectors
//
//  Copyright (C) 2019-present, Mark AJ Klik
//
//  This file is part of the lazyvec R package.
//
//  The lazyvec R package is free software: you can redistribute it and/or modify it
//  under the terms of the GNU Affero General Public License version 3 as
//  published by the Free Software Foundation.
//
//  The lazyvec R package is distributed in the hope that it will be useful, but
//  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License
//  for more details.
//
//  You should have received a copy of the GNU Affero General Public License along
//  with the lazyvec R package. If not, see <http://www.gnu.org/licenses/>.
//
//  You can contact the author at:
//  - lazyvec R package source repository : https://github.com/fstpackage/lazyvec


#include "api_helpers.h"
#include "api_proxy.h"

SEXP ALTVEC_EXTRACT_SUBSET_PROXY(SEXP x, SEXP indx, SEXP call)
{
  return ALTVEC_DISPATCH(Extract_subset, x, indx, call);
}

SEXP ALTREP_SERIALIZED_STATE_PROXY(SEXP x)
{
  return ALTREP_DISPATCH(Serialized_state, x);
}

SEXP ALTREP_COERCE_PROXY(SEXP x, int type)
{
  return ALTREP_DISPATCH(Coerce, x, type);
}

Rboolean ALTREP_INSPECT_PROXY(SEXP x, int pre, int deep, int pvec,
  void (*inspect_subtree)(SEXP, int, int, int))
{
  return ALTREP_DISPATCH(Inspect, x, pre, deep, pvec, inspect_subtree);
}

SEXP ALTREP_DUPLICATE_EX_PROXY(SEXP x, Rboolean deep)
{
  return ALTREP_DISPATCH(DuplicateEX, x, deep);
}

SEXP ALTREP_DUPLICATE_PROXY(SEXP x, Rboolean deep)
{
  return ALTREP_DISPATCH(Duplicate, x, deep);
}

static SEXP Registry = NULL;

static SEXP LookupClassEntry(SEXP csym, SEXP psym)
{
  for (SEXP chain = CDR(Registry); chain != R_NilValue; chain = CDR(chain))
    if (TAG(CAR(chain)) == csym && CADR(CAR(chain)) == psym)
      return CAR(chain);
    return NULL;
}

static SEXP LookupClass(SEXP csym, SEXP psym)
{
  SEXP entry = LookupClassEntry(csym, psym);
  return entry != NULL ? CAR(entry) : NULL;
}

static SEXP find_namespace(void *data) { return R_FindNamespace((SEXP) data); }
static SEXP handle_namespace_error(SEXP cond, void *data) { return R_NilValue; }

static SEXP ALTREP_UNSERIALIZE_CLASS(SEXP info)
{
  if (TYPEOF(info) == LISTSXP) {
    SEXP csym = ALTREP_SERIALIZED_CLASS_CLSSYM(info);
    SEXP psym = ALTREP_SERIALIZED_CLASS_PKGSYM(info);
    SEXP altrep_class = LookupClass(csym, psym);
    if (altrep_class == NULL) {
      SEXP pname = ScalarString(PRINTNAME(psym));
      R_tryCatchError(find_namespace, pname,
                      handle_namespace_error, NULL);
      altrep_class = LookupClass(csym, psym);
    }
    return altrep_class;
  }
  return NULL;
}

SEXP ALTREP_UNSERIALIZE_EX_PROXY(SEXP info, SEXP state, SEXP attr, int objf, int levs)
{
  SEXP csym = ALTREP_SERIALIZED_CLASS_CLSSYM(info);
  SEXP psym = ALTREP_SERIALIZED_CLASS_PKGSYM(info);
  int type = ALTREP_SERIALIZED_CLASS_TYPE(info);

  /* look up the class in the registry and handle failure */
  SEXP altrep_class = ALTREP_UNSERIALIZE_CLASS(info);
  if (altrep_class == NULL) {
    switch(type) {
    case LGLSXP:
    case INTSXP:
    case REALSXP:
    case CPLXSXP:
    case STRSXP:
    case RAWSXP:
    case VECSXP:
    case EXPRSXP:
      warning("cannot unserialize ALTVEC object of class '%s' from "
                "package '%s'; returning length zero vector",
                CHAR(PRINTNAME(csym)), CHAR(PRINTNAME(psym)));
      return allocVector(type, 0);
    default:
      error("cannot unserialize this ALTREP object");
    }
  }

  /* check the registered and unserialized types match */
  int rtype = ALTREP_CLASS_BASE_TYPE(altrep_class);
  if (type != rtype)
    warning("serialized class '%s' from package '%s' has type %s; "
              "registered class has type %s",
              CHAR(PRINTNAME(csym)), CHAR(PRINTNAME(psym)),
              type2char(type), type2char(rtype));

  /* dispatch to a class method */
  altrep_methods_t *m = (altrep_methods_t*) (CLASS_METHODS_TABLE(altrep_class));
  SEXP val = m->UnserializeEX(altrep_class, state, attr, objf, levs);
  return val;
}
