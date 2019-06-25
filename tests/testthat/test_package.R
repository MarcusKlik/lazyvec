
context("package")

test_that("package version", {

  v <- packageVersion("lazyvec")
  expect_equal(lazyvec:::lazyvec_version(),
    256 * as.integer(v[1, 1]) + 16 * as.integer(v[1, 2]) + as.integer(v[1, 3]))
})
