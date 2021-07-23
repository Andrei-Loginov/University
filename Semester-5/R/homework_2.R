library(dplyr)
library(ggplot2)

library(gridExtra)

Anderson.Darling.statistic.norm <- function(sample, mean = 0, sd = 4){
  n <- length(sample)
  sample <- sort(sample)
  ans <- 0
  for (i in 1:length(sample)){
    ans <- ans + (2*i - 1)*( pnorm(sample[i], mean, sd, log.p = TRUE) + log(1 - pnorm(sample[n - i + 1], mean, sd)) )
  }
  return (-n - ans / n)
}

make.staatistics.sample.norm <-function(length, nsamples, mean = 0, sd = 4){
  v <- numeric(nsamples)
  for (i in 1:length(v)){
    v[i] <- Anderson.Darling.statistic.norm(rnorm(length, mean, sd), mean, sd)
  }
  return (v)
}

Anderson.Darling.statistic.exp <- function(sample, rate = 1){
  sample <- sort(sample)
  n <- length(sample)
  ans <- 0
  for (i in 1:n){
    ans <- ans + (2*i - 1)*( pexp(sample[i], rate, log.p = TRUE) + log( 1 - pexp(sample[n - i + 1], rate) ) )
  }
  return (-n  - ans / n)
}

make.statistics.sample.exp <- function(length, nsamples, rate = 1){
  v <- numeric(nsamples)
  for (i in 1:nsamples){
    v[i] <- Anderson.Darling.statistic.exp(rexp(length, rate), rate)
  }
  return (v)
}

Anderson.Darling.statistic.gamma <- function(sample, shape = 1, scale = 1){
  sample <- sort(sample)
  n <- length(sample)
  ans <- 0
  for (i in 1:n){
    ans <- ans + (2*i - 1)*( pgamma(sample[i], shape, scale = scale, log.p = TRUE) + 
                               log(1 - pgamma(sample[n - i + 1], shape, scale = scale)) )
  }
  return (-n - ans / n)
}

make.statisctics.sample.gamma <- function(length, nsamples, shape = 1, scale = 1){
  v <- numeric(nsamples)
  for (i in 1:nsamples){
    v[i] <- Anderson.Darling.statistic.gamma(rgamma(length, shape, scale = scale), shape, scale)
  }
  return (v)
}

nsamples <- 500
lengthes <- c(100, 500, 1000, 1500, 2000)


scores <- numeric(0)
N <- numeric(0)
for (len in lengthes){
  scores <-c(scores, make.staatistics.sample.norm(len, nsamples))
  N <- c(N, rep(len, nsamples))
} 


data1 <- data.frame(Score = scores, N = N)
ecdf1 <- ggplot(data1, aes(x = Score)) + stat_ecdf(aes(color = factor(N)), 
                        geom = "step", size = 0.5) + labs(y = "ECDF", fill = "N", 
                              title = "A-D Statistics distributnion for different N") + 
  scale_colour_discrete("Size of Sample N")
qq1 <-ggplot(mapping = aes(x = sort(filter(data1, N == 2000)$Score), y = sort(filter(data1, N == 1500)$Score))) + 
  geom_point() +
  geom_abline(aes(slope = 1, intercept = 0), linetype = 2) + 
  labs(y = "Quantiles N = 2000", x = "Quantiles N = 1500", 
       title = "QQ for Norm. statistics,\n N = 2000 & 1500") + geom_smooth(method = "lm") + coord_fixed()

qq2 <-ggplot(mapping = aes(x = sort(filter(data1, N == 2000)$Score), y = sort(filter(data1, N == 1000)$Score))) + 
  geom_point() +
  geom_abline(aes(slope = 1, intercept = 0), linetype = 2) + 
  labs(y = "Quantiles N = 2000", x = "Quantiles N = 1000", 
       title = "QQ for Norm. statistics,\n N = 2000 & 1000") + geom_smooth(method = "lm") + coord_fixed()

qq3 <-ggplot(mapping = aes(x = sort(filter(data1, N == 2000)$Score), y = sort(filter(data1, N == 500)$Score))) + 
  geom_point() +
  geom_abline(aes(slope = 1, intercept = 0), linetype = 2) + 
  labs(y = "Quantiles N = 2000", x = "Quantiles N = 500", 
       title = "QQ for Norm. statistics,\n N = 2000 & 500") + geom_smooth(method = "lm") + coord_fixed()

grid.arrange(ecdf1, qq1, qq2, qq3, nrow = 2)

scores2 <- c(filter(data1, N == 2000)$Score, make.statistics.sample.exp(2000, 500, 1),
             make.statisctics.sample.gamma(2000, 500, 3, 4))
Distr <- c(rep("Norm", 500), rep("Exp", 500), rep("Gamma", 500))

data2 <- data.frame(Score <- scores2, Distr <- Distr)

ecdf <-ggplot(data2, aes(x = Score)) + stat_ecdf(aes(color = Distr), geom = "step") + 
    labs(title = "A-D statistics distribution", y = "")

qq1 <-ggplot(mapping = aes(x = sort(filter(data2, Distr == "Norm")$Score),
                           y = sort(filter(data2, Distr == "Exp")$Score))) + 
  geom_point() +
  geom_abline(aes(slope = 1, intercept = 0), linetype = 2) + 
  labs(y = "Normal Distribution statistics quantiles", x = "Exponential Distribution statistics quantiles", 
       title = "QQ for Normal and Exponential distributions") + geom_smooth(method = "lm") + coord_fixed()

qq2 <-ggplot(mapping = aes(x = sort(filter(data2, Distr == "Norm")$Score), 
                           y = sort(filter(data2, Distr == "Gamma")$Score))) + 
  geom_point() +
  geom_abline(aes(slope = 1, intercept = 0), linetype = 2) + 
  labs(y = "Normal and Distribution statistics quantiles", x = "Gamma Distribution statistics quantiles", 
       title = "QQ for Normal and Gamma distributions") + geom_smooth(method = "lm") + coord_fixed()
qq3 <-ggplot(mapping = aes(x = sort(filter(data2, Distr == "Gamma")$Score),
                           y = sort(filter(data2, Distr == "Exp")$Score))) + 
  geom_point() +
  geom_abline(aes(slope = 1, intercept = 0), linetype = 2) + 
  labs(y = "Gamma Distribution statistics quantiles", x = "Exponential Distribution statistics quantiles", 
       title = "QQ for Gamma and Exponential distributions") + geom_smooth(method = "lm") + coord_fixed()

grid.arrange(ecdf, qq1, qq2, qq3, nrow = 2)

