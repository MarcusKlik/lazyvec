
# adapted from https://tolstoy.newcastle.edu.au/R/help/05/04/2715.html

ones <- function(number) {
  c("", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine")[number + 1]
}


teens <- function(number) {
  c("ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", " seventeen", "eighteen", "nineteen")[number + 1]
}


tens <- function(number) {
  c("ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety")[number]
}


suffixes <- c("thousand", "million", "billion", "trillion")


makeNumber <- function(...) as.numeric(paste(..., collapse = ""))


number_to_text <- function(x) {

  # possibly scientific notation
  if (x > 2000000000) {
    if (x >= 1e15) stop("Number too large")

    digits <- as.integer(rev(strsplit(as.character(x %/% 1000000000), "")[[1]]))
    digits <- c(
      head(c(as.integer(rev(strsplit(as.character(as.integer(x %% 1000000000)), "")[[1]])), rep("0", 8)), 9),
      digits
    )
  } else {
    digits <- as.integer(rev(strsplit(as.character(as.integer(x)), "")[[1]]))
  }

  nDigits <- length(digits)

  # below 10
  if (nDigits == 1) return(ones(digits))

  # below 20
  if (nDigits == 2) {
    if (x <= 19) return(teens(digits[1]))
    
    return(paste(tens(digits[2]), ones(digits[1])))
  }

  if (nDigits == 3) {
    if (x %% 100 == 0) return(paste(ones(digits[3]), "hundred"))
    return(paste(ones(digits[3]), "hundred and", number_to_text(makeNumber(digits[2:1]))))
  }

  nSuffix <- ((nDigits + 2) %/% 3) - 1

  suffix_text <- paste0(
    number_to_text(makeNumber(digits[nDigits:(3*nSuffix + 1)])),
    " ",
    suffixes[nSuffix]
  )

  remainder <- makeNumber(digits[(3*nSuffix):1])
  if (remainder == 0) return(suffix_text)

  if (remainder < 100) {
    return(paste0(
      suffix_text,
      " and ",
      number_to_text(remainder)
    ))
  }
  
  paste0(
    suffix_text,
    ", ",
    number_to_text(remainder)
  )
}


numbers_to_words <- function(x){
  x <- round(x)

  if (length(x) > 1) return(sapply(x, number_to_text))

  number_to_text(x)
}


helpers <- list(
  ones = ones,
  teens = teens,
  tens = tens,
  suffixes = suffixes,
  makeNumber = makeNumber,
  number_to_text = number_to_text,
  numbers_to_words = numbers_to_words
)


lazyvec_length <- function(x) {
  length(x[[1]])
}


lazyvec_full_vector <- function(x) {
  numbers_to_words(x[[1]])
}


lazyvec_element <- function(x, i) {
  number_to_words(x[[1]][i])
}


lazyvec_is_sorted <- function(x) {
  FALSE
}


lazyvec_no_na <- function(x) {
  TRUE
}


lazyvec_extract_subset <- function(x, index) {
  numbers_to_words(x[[1]][index])
}


# define int_range ALTREP API
lazyvec_api <- lazyvec_methods(
  lazyvec_length,
  lazyvec_full_vector,
  lazyvec_element,
  lazyvec_is_sorted,
  lazyvec_no_na,
  lazyvec_extract_subset
)


# constructor for an custom integer range
number_word <- function(range) {
  
  # alternative representation
  alt_pres <- list(
    range = range,     # range
  )
  
  # return custom ALTREP vector
  lazyvec(alt_pres, "character", lazyvec_api, helpers)
}
