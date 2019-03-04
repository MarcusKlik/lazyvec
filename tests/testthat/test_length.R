
context("length")

match_output <- function(output, message) {
  -1 %in% regexpr(message, output, fixed = TRUE)
}

test_that("ALTREP length diagnostic message", {
  output <- capture.output(alt_wrap(1:20, "x"))

  expect_true(match_output(output, "result = integer[1] 20"))
})
