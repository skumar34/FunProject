# Author : Sanjeev Kumar
# Modification History : 1.04.2016 Creation Date

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


# Clustering is mostly used in absence of target varaibles to search for relationship between input variables
# Hierarchical Clustering(Using Euclidean and Centroid): This technioque combines the two nearest clusters in the same cluster.
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

# Cluster MRI Images by tissue substances and locate pathological anatomlies.
# Image Segmentation : Divide the image into regions/clusters corresponding to individual surfaces, objects or natural parts of object.
# Segments should be meaningful(most important). Various methods are proposed to segment the images. 
# 1. Clustering Methods : Partition image to clusters based on differences in pixel color , intensity or texture.
# 2. Edge Detection : Based on the  detection of discontinuity, such as an abrupt change in grey level in grey-scale images.
# 3. Region-growing methods : Divide image into regions, then sequentially merge sufficiently similar regions.

# Let start with a simple example of clustering Pixels using greyscale images.
# Greyscale image : Matrix of pixel intensity values ranging from 0(black) to 1(white). For 8bit/pixel we have 256 color levels.
# Greyscale image segmentation is done by clustering pixels according to their intensity values.
# What are the inputs to clustering algo? Observation are vector containing each pixel intensity value and a single variable i.e intensity value.
# Most Important step before feeding intensity values to the clustering algo is morphing our data i.e lump all intensity values into a single vector.

flower_data = read.csv("flower.csv", header = FALSE)
str(flower_data)

# So what is observed in str(flower_data). r treats the rows as observations and columns as variables.
# So need to change the data type to matrix
flowerMatrix = as.matrix(flower_data)

# as.vector stores the matrix as vector column wise if with default options. 
# Q: Why not we directly convert the data to vector instead of converting data to matrix and then vector? Hint: Ans lies in above comments.
flowerVector = as.vector(flowerMatrix)
distance = dist(flowerVector, method = "euclidean")
str(flowerVector)
# ward.D method is the minimum variance method which trying to find compact and spherical clusters
clusterIntensity = hclust(distance, method = "ward.D")
plot(clusterIntensity)
image(flowerClusters, axes=FALSE)
rect.hclust(clusterIntensity, k=3, border="red")
flowerClusters = cutree(clusterIntensity, k =3)
flowerClusters
tapply(flowerVector, flowerClusters, mean)

# This will convert flower cluster into a 50 x 50 matrix 
dim(flowerClusters) = c(50,50)
image(flowerClusters, axes=FALSE)
image(flowerMatrix, axes=FALSE, col = grey(seq(0,1,length=256)))

###############################################################################################################################
# Now segment the MRI image of a healthy patient using hierarchical clustering
healthy = read.csv("healthy.csv", header = FALSE)
healthyMatrix = as.matrix(healthy)
str(healthyMatrix)
image(healthyMatrix, axes=FALSE, col = grey(seq(0,1,length=256)))

# convert healthy matrix to vector
healthyVector = as.vector(healthyMatrix)

# The first step in hierarchical clustering is computing the distance matrix
distance = dist(healthyVector, method = "euclidean")
str(healthyVector)
n = length(healthyVector)
# So a distance vector have n*(n-1)/2 values
n*(n-1)/2
# if each cell in the matrix takes 4 bytes then the number showing represents the amount of memory 
# required in GB's
# 2 : Symmetric matrix , +n for diagonal elements.
(2*n*(n-1)*2+n)/(1024*1024*1024)
# So it means that by this way we cannot use hierarchial clustering. So is there any pther means to use clustering.
# k-means clustering 
# 1. Specify the number of clusters. But how? Setting the number of clusters depends on what are you trying to extract from 
#    the image. e.g no of grey maater or white matter
k = 5
set.seed(1)
KMC = kmeans(healthyVector, centers = k, iter.max = 1000)
str(KMC)
healthyClusters = KMC$cluster
# How can we obtain the mean intensity value within each of the 5 clusters.
KMC$centers
KMC$size

# If we notice that laargest cluster is cluster number 3 of size 133162 but have the lowest mean intensity value.
# This means that the possible cluster number 3 can be the darkest shade in the MRI image.And again notice on the 
# mean intensity of each cluster , all are less than 0.5 i.e the image is pretty dark.
# Now convert healthyCluster Vector to matrix
dim(healthyClusters) = c(nrow(healthyMatrix), ncol(healthyMatrix))
image(healthyClusters, axes=FALSE, col = rainbow(k))

# ANother way of selecting the number of clusters is using the scree plot which works for any clustering algorithm.
# A standard scree plot have number of cluster on the x-axis and within-cluster  sum of squares on y axis.
# What is this within-cluster sum of squares ? For a given cluster it is the squared distance between each point and the 
# the centroid of the cluster.

KMC2 = kmeans(healthyVector, centers = 2, iter.max = 1000)
KMC2$withinss
NumClusters = seq(2,10,1)
SumWithinss = sapply(2:10, function(x) sum(kmeans(healthyVector, centers=x, iter.max=1000)$withinss))
# You will find in the scree plot that after 5 clusters the bend is smoother. So number of cluster =5 may be adequate.
plot(NumClusters, SumWithinss, type="b")


################ Now DETECT TUMOR WITH OLIGODENDROGLIOMA : A tumor that commonly occurs in the front lobe of the brain.
# The brain biopsy is the only definite diagnosis of this tumor. So MRI gudiance is key in determining it's location and geometry.
tumor = read.csv("tumor.csv", header = FALSE)
tumorMatrix = as.matrix(tumor)
tumorVector = as.vector(tumorMatrix)

# So how we proceed? 
# Apply the clustering results of healthy patient MRI image to this one or treat healthy vector as a training set and
# tumorVector as the test set. To do that we require a new package called flexclust
install.packages("flexclust")
library("flexclust")

# The flexclust package contains the library called kcca which stand for k centroid cluster analysis.
# We need to convert the information from clustering algorithm to the object of the class kcca and need before doing predict 
# function on the tumor test set data.
KMC.kcca = as.kcca(KMC, healthyVector)
tumorClusters = predict(KMC.kcca, newdata = tumorVector)
dim(tumorClusters) = c(nrow(tumorMatrix), ncol(tumorMatrix))
image(tumorClusters, axes=FALSE, col=rainbow(k))
