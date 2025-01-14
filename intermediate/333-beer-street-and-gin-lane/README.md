
# [2017-09-27] Challenge #333 [Intermediate] Beer Street and Gin Lane

[/r/dailyprogrammer](https://www.reddit.com/r/dailyprogrammer/comments/72s7xp/20170927_challenge_333_intermediate_beer_street/)

## Description

The US state of Iowa has relesed over a year's worth of liquor sales data, great for data mining. In this practical exercise we'll be asking you to do some large scale data analysis. Hopefully this data set is big enough that you have to make some decisions about data structures and algorithms and don't just `sort | uniq`.

This particular challenge differs from many we do because I anticipate you'll use languages and tools such as `SQL`, `LINQ`, and similar, although if you feel like using a more conventional programming language please do. My objective with this particular challenge is to explore a data science type of a challenge, inspired by some comments earlier this year seeking more practical challenges.
The title of this challenge refers to [artwork by William Hogarth](https://en.wikipedia.org/wiki/Beer_Street_and_Gin_Lane).

## Questions to Answer

EDIT After reading [this comment](https://www.reddit.com/r/dailyprogrammer/comments/72s7xp/20170927_challenge_333_intermediate_beer_street/dnkzeff/?utm_content=permalink&utm_medium=front&utm_source=reddit&utm_name=dailyprogrammer) that does a great job explaining the data set (I had misinterpreted it when I wrote this up), i edited the questions. Also I don't think Iowa tracks beer sales in this category.

* For beer sales across Iowa (e.g. where someone buys beer, not just any alcohol), what is the most popular street name across all cities?
* What's the most popular non-beer beverage bought in 2016?
* What store has made the most profit (the difference between the state cost per bottle and the sales price per bottle times the quantity of all bottles sold)?
* What are the top types of alcohol commonly bought together? (e.g. "wine and tequila")
* What day of the week sees the most vodka sales?
* Which streets in Iowa are really Beer Street and Gin Lane?
* NEW Where in the world is all of that root beer schnapps going?

Challenges for you to consider include runtime analysis and performance.

Feel free to highlight any insights you find and how you found them - that's in scope for this challenge.

## Get the Data

You can get [the data](https://data.iowa.gov/Economy/Iowa-Liquor-Sales/m3tr-qhgy) on the Iowa data website. Export it to get it into a format (e.g. CSV) suitable for coding - don't bother trying to scrape it!

## Notes

Some links that may be useful
[Harvard CS 229r: Algorithms for Big Data](http://people.seas.harvard.edu/%7Eminilek/cs229r/)
[Data Structures and Algorithms for Big Databases presentation](http://www.slideshare.net/omnidba/data-structures-and-algorithms-for-big-databases)
[SQL Introduction](https://www.w3schools.com/sql/sql_intro.asp)
[LINQ Introduction](http://csharp-station.com/Tutorial/Linq/Lesson01)