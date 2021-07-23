data.set <- read.table("http://statmod.ru/wiki/_media/study:fall2020:dataprog:quakes.txt", header = TRUE, sep = "\t")
data.set <- select(data.set, -1)
summary(data.set)
head(data.set)

library(dplyr)

df <- data.set
df <- mutate(df, depth = depth * 3280.839895)

degreesToRadians <- function(degrees){
  return (degrees * pi / 180)
}


distance <- function(lat1, lon1, lat2, lon2){
  lat1 <- degreesToRadians(lat1)
  lon1 <- degreesToRadians(lon1)
  lat2 <- degreesToRadians(lat2)
  lon2 <- degreesToRadians(lon2)
  return (6367.44 * 2 * asin( sqrt( (sin((lat2 - lat1)/2))^2 + cos(lat1) * cos(lat2) * (sin( (lon2 - lon1) / 2 )^2 ) ) ))
}

SPb.lat <- 59.939095
SPb.long <- 30.315868

df <- mutate(df, direct =  distance(lat, long, SPb.lat, SPb.long))

df <- filter(df, mag >= 5)
write.table(df, file = "new_data.txt", sep = "\t", row.names = FALSE)

print(paste0("Fiji archipelago located in area (", min(data.set$lat), ", ", max(data.set$lat), ") latitude, (", min(data.set$long), ", ", max(data.set$long), ") longitude"))

print(paste("The deepest event had magnitude", data.set$mag[data.set$depth == max(data.set$depth)]))


df1 <- arrange(data.set, desc(stations))
df1[1:5,]


