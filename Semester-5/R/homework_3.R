library(ggplot2)

ggplot(quakes, mapping = aes(x = long, y = lat)) + stat_density_2d(aes(fill = ..level..), geom = "polygon") + 
  scale_fill_continuous(low = "lavenderblush", high = "red") + 
  labs(y = "Latitude", x = "Longitude", title = "Relationship between latitude and longitude", fill = "Density")


quakes$mag.intervals <- cut(quakes$mag, 12)
quakes$mag.factor <- cut(quakes$mag, 4)

ggplot(quakes, mapping = aes(x = depth, y = stations, color = mag.intervals))+
  geom_point(size = 1.3, alpha = 0.5) +
  labs(x = "Depth", y = "Stations",
       title = "Event magnitude distribution based on depth and number of stations reporting",
       fill = "Magnitude intervals")+
  facet_grid(.~mag.factor)

ggplot(quakes, mapping = aes(x = mag)) +
  geom_density(color = "blue", fill = "light blue", size = 1, alpha = 0.5) + 
  labs(x = "Magnitude", title = "Magnitude density")
