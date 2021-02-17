# Six Degrees of Kevin Bacon
Six Degrees of Kevin Bacon is game where the goal is to find the shortest path from an arbitrary actor to Kevin Bacon through a movie which both actors participated together

### Example
In option 1, you can search for the KB of an arbitrary actor. You can use the ```input-top-grossing.txt``` to facilitate you. The names need to be written as **Last Name, Name**.
Use option 2 to exit.

Let's suppose that you want to find the KB of **De Niro, Robert**. According to ```input-top-grossing.txt```, the output would be:
```
'De Niro, Robert' has KB = 3
'De Niro, Robert' acted in 'Analyze This (1999)' with 'Viterelli, Joe'
'Viterelli, Joe' acted in 'Firm, The (1993)' with 'Harris, Ed'
'Harris, Ed' acted in 'Apollo 13 (1995)' with 'Bacon, Kevin'
```


### Compiling
```
make all

```
### Executing
```
make run

```

### Cleaning execution data
```
make clean

```
