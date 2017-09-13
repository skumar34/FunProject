# Author : Sanjeev Kumar <sanjeevk2017@email.iimcal.ac.in>
# Date of Creation : 04. 02. 2017
# It computes the mle estimates for truncated data set

ll_Normal=function(param, data, llim, rlim){
  mu = param[[1]]
  sigma = param[[2]]
  # By default optim searches for parameters which minimise the function i.e ll_Normal . So in order to find
  # maximum multiply the loglikelihood by -1.
  -sum(dnorm(data, mean = mu, sd = sigma, log = TRUE)-log(pnorm(rlim, mean=mu, sd = sigma)-
                                                            pnorm(llim,mean=mu,sd=sigma)))
}

ll_Weibull=function(param, data, llim, rlim){
  # shape parameter
  k = param[[1]]
  # scale parameter
  lambda = param[[2]]
  # By default optim searches for parameters which minimise the function i.e ll_Normal . So in order to find
  # maximum multiply the loglikelihood by -1.
  -sum(dweibull(data,shape = k, scale = lambda, log = TRUE) - log(pweibull(rlim, shape = k,scale = lambda)
                                                                  -pweibull(llim, shape = k, scale = lambda)))
}

# Load the dataSet
print("Select the File containing the CGPA Data")
cgpa_data = read.csv(file.choose(),header=TRUE)

# Set the left and right hand side limits
left = 5
right = 9
hist(cgpa_data$CGPA)
skewness = 3*(mean(cgpa_data$CGPA)-median(cgpa_data$CGPA))/sd(cgpa_data$CGPA)
# Fit the MLE for Normal Distribution
optim(par=c(mean(cgpa_data$CGPA),sd(cgpa_data$CGPA)), fn = ll_Normal, data = cgpa_data$CGPA,llim=left,rlim=right)

# Fit the MLE for Weibull Distribution
k = 1
lambda = 1
optim(par=c(k,lambda), fn=ll_Weibull, data = cgpa_data$CGPA, llim = left, rlim=right)