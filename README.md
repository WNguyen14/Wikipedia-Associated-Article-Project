# Wikipedia-Associated-Article-Project

## Reference:
https://consonni.dev/datasets/wikilinkgraphs/

## Structure of csv file:

| page_id_from |   page_title_from | page_id_to    |  page_title_to |
| ------------ | ----------------- | ------------- | -------------- |
|10      |AccessibleComputing     |411964  |Computer accessibility
|12      |Anarchism       |5013592 |6 February 1934 crisis
|12      |Anarchism       |2181459 |Abstentionism
|12      |Anarchism       |839656  |Adolf Brand
|12      |Anarchism       |2731583 |Adolf Hitler
|12      |Anarchism       |192008  |Adolphe Thiers
|12      |Anarchism       |729048  |Affinity group
|12      |Anarchism       |30758   |Age of Enlightenment
|12      |Anarchism       |627     |Agriculture
|12      |Anarchism       |710931  |AK Press

## Download: 
https://zenodo.org/record/2539424/files/enwiki.wikilink_graph.2018-03-01.csv.gz?download=1

This is the csv file for all of the edges in wikipedia in 2018 for English, after extraction its like 9gb

## Notes:

1. Opening the csv file in excel and then copying the data might add quotation marks to the data? 
2. Not all ids are used
3. BST works!
4. Adj Matrix & Edge List seem to be very computationally expensive, doesn't work?
