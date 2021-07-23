data(Chem97, package = "mlmRev")
xtabs( ~ score, data = Chem97)
library("lattice")
library("ggplot2")
library(dplyr)

ggplot(Chem97, mapping = aes(x = gcsescore))+
  geom_histogram()+ 
  facet_wrap(~factor(score), nrow = 2)


ggplot(Chem97, mapping = aes(x = gcsescore))+
  geom_density(color = "blue") + 
  facet_wrap((~score), nrow = 2)+
  labs(y = "Density")



ggplot(Chem97, aes(gcsescore)) + 
  geom_density(aes(colour = factor(score))) +
  theme(legend.position = "top")


ggplot(as.data.frame(Titanic), aes(Freq, Class, fill = Survived)) + 
  geom_bar(stat = "identity") + facet_wrap(~Age + Sex, nrow = 1)+
  theme(legend.position = "top")



ggplot(as.data.frame(Titanic), aes(Freq, Class, fill = Survived)) + 
  geom_bar(stat = "identity") + facet_wrap(~Age + Sex, nrow = 1, scales = "free")+
  theme(legend.position = "top")



ggplot(Chem97, aes(sample = gcsescore)) + stat_qq(color = "blue", alpha = 0.5, shape = 1) +
  facet_wrap(~score) + 
  labs(y = "gcsescore")

ggplot(Chem97, aes(sample = gcsescore)) + 
  stat_qq(aes(colour = factor(score)), shape = 1, alpha = 0.5)+
  facet_wrap(~factor(gender)) + 
  labs(x = "Standard Normal Quantiles", y = "Average GCSE Score")



Chem97.mod <- transform(Chem97, gcsescore.trans = gcsescore^2.34)

ggplot(Chem97.mod, aes(sample = gcsescore.trans))+
  stat_qq(aes(colour = factor(score)), shape = 1, alpha = 0.5) + 
  facet_wrap(~factor(gender)) + 
  labs(y = "Transformed GCSE Score", x = "Standard Normal Quantiles") 


ggplot(Chem97, aes(factor(score), gcsescore)) +
  geom_boxplot() + 
  facet_wrap(~gender) +
  coord_flip() + 
  labs(y = "Average GSCE Score")


ggplot(Chem97, aes(factor(score), gcsescore^2.34)) +
  geom_boxplot() + 
  facet_wrap(~gender) + 
  labs(y = "Transformed GCSE Score")

library("latticeExtra")
data(gvhd10)  

ggplot(gvhd10, aes(log(FSC.H))) + 
  geom_density() + 
  facet_wrap(~Days, ncol = 2, as.table = FALSE)

log.range = range(log2(gvhd10$FSC.H))
ggplot(gvhd10, aes(log2(FSC.H))) + 
  facet_wrap(~Days, as.table = FALSE, ncol = 2) + 
  geom_histogram(binwidth = (log.range[2] - log.range[1]) / 50)+
  labs(x = "log Forward Scatter")

ggplot(gvhd10, aes(x = factor(Days), y = log(FSC.H))) + 
  geom_boxplot() + 
  coord_flip() + 
  labs(y = "Days Past Transplant", x = "log(Forward Scatter)")

ggplot(gvhd10, aes(x = factor(Days), y = log(FSC.H))) + 
  geom_violin(fill = "#33FFF1") + 
  coord_flip() + 
  labs(y = "log(Forward Scatter)", x = "Days Past Transplant")

ggplot(quakes, aes(depth, factor(mag))) + 
  geom_point(shape = 1, colour = "blue")+
  labs(y = "")

ggplot(quakes, aes(x = factor(mag), y = depth)) + 
  geom_jitter(shape = 1, colour = "blue", alpha = 0.6, width = 0.1) + 
  labs(x = "Magnitude (Richter)", y = "Depth (km)") 

quakes <- mutate(quakes, Depth = cut(quakes$depth, 2))
ggplot(quakes, aes(long, lat)) + 
  geom_point(colour = "blue", shape = 1) + 
  facet_wrap(~Depth)


quakes <- mutate(quakes, Depth = cut(quakes$depth, 3))
ggplot(quakes, aes(long, lat)) + 
  coord_equal() + 
  geom_point(colour = "blue", size = 0.8) +  
  facet_wrap(~Depth) + 
  labs(x = "Longitude", y = "Latitude")

quakes <- mutate(quakes, Depth = cut(depth, breaks = quantile(depth, ppoints(4, 1))))
ggplot(quakes, aes(long, lat, colour = Depth)) + 
  geom_point(shape = 1) + 
  labs(y = "Latitude", x = "Longitude", title = "Depth") + 
  coord_equal() + 
  theme(legend.position = "top")


ggplot(quakes, aes(long, lat, colour = factor(cut(depth, 100, label = FALSE)))) + 
  geom_point(size = 5) + 
  coord_equal() + 
  theme(legend.position = "none") + 
  scale_colour_grey() + 
  labs(x = "Longitude", y = "Latitude")

