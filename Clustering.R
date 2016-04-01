# Netflix Movie Dataset
# There are two types of data 
#                 1) Every Movie in Netflix db has ranking from all users
#                 2) Facts about the movie itself i.e actors, directors, genre classifications, year released etc.
# Collaborative Filtering : The technique of Using other users rating to predict the rating of not rated movie by 
#                           some user is called collaborative filtering. It doesn't take the nature of item in consideration
#                           It requires a lot of data to make accurate recommendation.
# Cotent Filtering : Based on already rated movie by some user and recommend that user another movie of same director, 
#                    genre, actor etc. This type of technique is called content filtering.
#                   It requires very little data to get started but has limited scope.
#                   Here we will use this method using technique called clustering
# Netflix actually used both content and collaborative filtering called hybrid recommendation system.
# For clustering we have to find the similarity between the datapoints. So simplest measure for finding the similarity 
# between datapoints is euclidean distance. Other meausures are Manhattan Distance and maximum coordinate distance. 
# Another measure we use is the distance between the cluster. The most common distance metric between the clusters is called centroid
# distance. If the variables are not on the same scale then we need the normalization.



# Hierarchical Clustering(Using Euclidean and Centroid): This technioque combines the two nearest clusters in the same cluster.
# 
# Load the Movie lens dataset and prepare the dataset
movies = read.table("Movielens.txt", header=FALSE, sep="|", quote="\"")
str(movies)
colnames(movies) = c("ID","Title","ReleaseDate","VideoReleaseDate","IMDB","Unknown","Action","Adventure","Animation",
                     "Childrens","Comedy","Crime","Documentary","Drama","Fantasy","FilmNoir","Horror","Musical", "Mystery",
                     "Romance","SciFi","Thriller","War","Western")
str(movies)
# Since we are not using the ID , ReleaseDate, Videoreleasedate, IMDB . So remove these columns
movies$ID = NULL
movies$ReleaseDate = NULL
movies$VideoReleaseDate = NULL
movies$IMDB = NULL
# And if there are some duplicate entries in the data set, then we need to remove that by remove function.
movies = unique(movies)

str(movies)
table(movies[,2:20])

# Now apply the heirarchical clustering. There are two steps for heirarchical clustering. 
# 1. Compute the distances between all the data points. Distances can be computed using the dist function(euclidean diatnces)
# 2. Cluster those data points.
distances = dist(movies[,2:20], method="euclidean")

# The ward.D method cares about the diatnace between clusters using centroid distance and also variances in each of the cluster.
clusterMOvies = hclust(distances, method ="ward.D")
# Plot the dendogram
plot(clusterMOvies)
clusterGroups = cutree(clusterMOvies, k =10)
# compute the % of movies in each genre and each cluster. It divides our datapoints into 10 clusters and compute the
# average of Action variable for each cluster. Since Action is the binary variable , so the mean measure gives the
# % of movies in action genre that particular group.
tapply(movies$Action, clusterGroups, mean)
tapply(movies$Romance, clusterGroups, mean)

# Lets figure out Men in Black belongs to which cluster
subset(movies, Title=="Men in Black (1997)")
clusterGroups[257]
cluster2 = subset(movies, clusterGroups == 2)
cluster2$Title[1:10]


######################################################################################################################
# Predictive diagnosis : Discovering patterns in disease detection
# Clustering Methods : spectral clustering and k-means clustering
# k-means clustering :
#       1. specify desired number of clusters k
#       2. Randomly assign each data point to a cluster
#       3. compute the cluster centroids
#       4. Reassign each point to closest cluster centroid
#       5. Re-compute cluster centroids
#       6. Repeat 4 and 5 until no improvement is made.


