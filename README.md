# PA-Tema1

## Walsh
In order to solve this task, I made use of the code for the first lab, where I implemented the Z-traversal (Z-parcurgere). I used a Divide and conquer algorithm, where based on given square positions and square size, I choose what subsquare to enter. In order to find the value in the Walsh matrix, I will count how many times I enter the fourth square (right, down) and the parity will influence whether the value is 1 (for odd) or 0 (for even).  
  
Time complexity: O(n)  
Space complexity: O(n)  


## Statistics
For this task, I created a structure for every word where I keep the length and a frequency alphabet vector for the letters inside the given string, as well as the value of a current position. Then, I use a Greedy algorithm, by iterating through the letters of the alphabet and incrementing every current position field in the array of words. The word structures  are sorted based on the current letter's dominance. I iterate through the sorted words and stop when the letter doesn't have dominance anymore over the concatenated string. Then, I check if the current number of words has the maximum value or not. not. First I used quicksort instead of the C++ function sort, and that generated a TLE for many of the tests. I solved this problem by including the current position field in the word structure in order to not use it as a parameter in the compare function.  
  
Time complexity: O(n * log n)  
Space complexity: O(n)  
  

## Prinel
I used two Dynamic Programming algorithms to get the maximum number of points. I find the maximum value in the target array, and then count the number of operations for every number up to the maximum value (1 to max). For every power of 2, the number of operations will be equal to the the previous power of 2's incremented number of operations. However, if the number is not of type 2^x, then the result will be based on another value's (from last power of 2 to current number) if heir difference is a divisor.  
After all number of operations were calculated, I use the 0-1 Knapsack algorithm (alternate Backpack) to get the maximum earned points. Thus, I compare the cases where an object is included or not and keep the maximum value. In the end, the maximized number of points will be situated on the last column of the last line.  

However, I made the discovery that the maximum number of operations up to 10^5 is 24. This means that if there are 1000 numbers, the total number of operations will be smaller than 24 * 1000 = 24. This means that if the target weight is greater than 24000, I don't need to calculate the number of operations, I can just calculate the sum of points, because the total number of operations would have a lower value than 24000.  
  
Time complexity: O(op * n)  
Space complexity: O(op * n)  


## Crypto
In order to calculate the number of times a given string str2 can be a substring of a longer string str1, I used a Dynamic Programming algorithm. I create a matrix of size n * m (one row for each character in str1 and  one column for each character in str2, plus an extra row and column). The  value of dp[i][j] is the number of times str2[1 ... j] appears as a substring in str1[1 ... i].  

At each step, I compare one chracter from str1 and one character from str2,  and there are 3 cases. The first is when the characters don't match and no '?' was found, meaning the current letter in str1 can't be in the substring and thus won't affect the result, so I copy the result for the same substring of the previous character in str1. However, when the letters do match, I'll add together the result from the previous row and column (those are substrings that will be continued by the current letter in str2) and the one from the previous row but the same column (the substrings we had found up to the previous character in str1). In case of a '?' in str1, I apply the second case for every  column and multiply the result of dp[i-1][j] by the number of letters there are  in str2, because that's how many "new" strings we will get.

Time complexity: O(m * n)  
Space complexity: O(m * n)
