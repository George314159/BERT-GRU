# GRU BERT

## Introduction

As we know, sentimental analysis, which extracts the subjective information from the reviews, has helped many companies to better understand their customers and products. From the text mining and natural language processing, we can infer the features of a product that customers pay more attention to, and customers’ underlying thoughts about the products. As a result, we would like to classify the polarity of the customer reviews, and to predict the sentimental score by the natural language processing techniques.

## Model

First of all, we would like to use Recurrent Neural Network for our task, specifically, the Gated Recurrent Unit (GRU). We choose the GRU for the following reasons. First, GRU helps solving the exploding and vanishing gradients issue that may happen in a normal Recurrent Neural Network. In addition to that, GRU is more efficient than the LTSM model, which has similar functionality with GRU. The Mathematical Equations for GRU are as follows, which described the update gate, reset gate, current memory, and final memory.

## Modifications and Improvements

Nevertheless, we would like to modify the general GRU model in order to improve the performance and accuracy. We will approach this ultimate goal by the following three main modifications: 1) Make the model bi-directional, 2) Adding layers to the model. 3) Embedding the input sentences by Bert Tokenizer.

### Bi-directional Modification

In the NLP problems, the bi-directional technique is an important way to improve the model’s performance. The Bidirectional networks could interpret the meanings of the words in two directions by applying forward propagation two times with different directions. As a result, the forward propagation is completed in two steps: first go forward in time, which helps model learn from the prior word and then go back in time, which helps model learn the future word. By doing this, we could better understand the words from the context.

### Multi-layer Modification

In order to further improve our model, we would like to add more layers to our model. We will stack multiple layers on top of each other in order to achieve better results. But adding too many layers will be computationally expensive. As a result, for our model, we will only use two layers in order to be efficient.

### Embedding by BERT Tokenizer Modification

The last modification will be on the embedding process. Instead of normal bag-of-words embeddings which utilizes frequency of words to form tokens, we would like to use the pre- trained tokenizer from Bidirectional Encoder Representations from Transformers, or BERT. The reason why we would like to utilize this technique is that BERT is the State-of-the-Art pre- training for Natural Language Processing. We would like to use the BERT-Base Uncased model, which contains 12 layers, 768 hidden layers, 12 heads, and 110 million parameters.


## Datasets

The dataset we used is from Kaggle, which contains various customer reviews about products such as Kindle and Fire TV from Amazon.com. There are overall 34,659 reviews. Each review has 21 different features such as link, name, review date, et cetera. Nevertheless, the only useful and relevant features for performing our sentiment analysis will be the ratings and the review body. In order to embed the review body, as mentioned, we will use BERT Tokenizer to transfer the sentences to vectors. In addition to that, we will make the vectors the same by padding 0s if less than the desired length or splitting if larger than the desired length. After that, we will transfer the embedded vectors to tensors. On the other hand, we will treat the rating scores as binary representation. if it’s larger than 4, the representation will be 1. Or it will be 0. As a result, for one training point, we will have our embedded tensors for the review body as X value, and the binary representation for the rating scores as y values for our classifier. In addition to this, we will split the data by 80%/10%/10% for training, validation, and testing set. As a result, our total count of training points will be 27727.


## Results

We use Grid Search to find the best set of hyperparameters for our model. Specifically, the hyperparameters we tuned include dimension of hidden states, number of layers and regularization terms. To evaluate the performance of our model, we choose the  model evaluation metrics - precision and recalls.In the end, we achieved precision of 0.67 and recall of 0.69. It means roughly 70% of the positive identifications are actually correct and roughly 70% of the actual positive sentiments have been identified correctly from our predictions. The result meets our previous expectations, while we do realize that there is plenty of room for improvements. For example, in this project we label ratings with 4.0 or above to “Positive”, which can be over-simplified. A potential better approach is to test multiple cutoff values to decide how high the rating should actually be to be considered a positive attitude.



## Contributors

* **Yifeng Hua** - *Initial work* 
* **Xiang Lu** - *Initial work* 
