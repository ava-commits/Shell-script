Shell Script: 

Write a shell script program for different string handling functions. 
#!/bin/bash 
# Function to find the length of a string 
string_length() { 
echo "Enter a string:" 
read str 
echo "Length of the string is: ${#str}" 
} 
# Function to compare two strings 
string_compare() { 
    echo "Enter first string:" 
    read str1 
    echo "Enter second string:" 
    read str2 
  if [ "$str1" == "$str2" ]; then 
        echo "Strings are equal." 
    else 
        echo "Strings are not equal." 
    fi 
} 
# Function to concatenate two strings 
string_concatenate() { 
    echo "Enter first string:" 
    read str1 
    echo "Enter second string:" 
    read str2 
    echo "Concatenated string: $str1$str2" 
} 
 
# Function to extract a substring 
string_substring() { 
    echo "Enter a string:" 
    read str 
    echo "Enter the starting position (0-based index):" 
    read start 
    echo "Enter the length of the substring:" 
    read length 
    echo "Extracted substring: ${str:$start:$length}" 
} 
 
# Function to reverse a string 
string_reverse() { 
    echo "Enter a string:" 
    read str 
    echo "Reversed string: $(echo $str | rev)" 
} 
 
# Function to check if a string contains a substring 
string_contains() { 
    echo "Enter the main string:" 
    read main 
    echo "Enter the substring to search for:" 
    read sub 
    if [[ $main == *"$sub"* ]]; then 
        echo "Substring found." 
    else 
        echo "Substring not found." 
    fi 
} 
 
# Main menu 
while true; do 
    echo "" 
    echo "String Handling Functions" 
    echo "1. Find string length" 
    echo "2. Compare strings" 
    echo "3. Concatenate strings" 
    echo "4. Extract substring" 
    echo "5. Reverse string" 
    echo "6. Check if string contains substring" 
    echo "7. Exit" 
    echo "Choose an option:" 
    read choice 
 
    case $choice in 
        1) string_length ;; 
        2) string_compare ;; 
        3) string_concatenate ;; 
        4) string_substring ;; 
        5) string_reverse ;; 
        6) string_contains ;; 
        7) echo "Exiting..."; exit 0 ;; 
        *) echo "Invalid choice. Please try again." ;; 
    esac 
done 
 
 
Write a shell script program for different arithmetic functions, example-grading systems 
#!/bin/bash 
 
# Function for basic arithmetic operations 
arithmetic_operations() { 
    echo "Enter the first number:" 
    read num1 
    echo "Enter the second number:" 
    read num2 
 
    echo "Choose an operation:" 
    echo "1. Addition" 
    echo "2. Subtraction" 
    echo "3. Multiplication" 
    echo "4. Division" 
    echo "5. Modulus" 
    read operation 
 
    case $operation in 
        1) echo "Result: $((num1 + num2))" ;; 
        2) echo "Result: $((num1 - num2))" ;; 
        3) echo "Result: $((num1 * num2))" ;; 
        4)  
            if [ $num2 -eq 0 ]; then 
                echo "Error: Division by zero is not allowed." 
            else 
                echo "Result: $((num1 / num2))" 
            fi 
            ;; 
        5) echo "Result: $((num1 % num2))" ;; 
        *) echo "Invalid operation." ;; 
    esac 
} 
 
# Function for grading system 
grading_system() { 
    echo "Enter the marks (out of 100):" 
    read marks 
 
    if [ $marks -ge 90 ]; then 
        echo "Grade: A" 
    elif [ $marks -ge 80 ]; then 
        echo "Grade: B" 
    elif [ $marks -ge 70 ]; then 
        echo "Grade: C" 
    elif [ $marks -ge 60 ]; then 
        echo "Grade: D" 
    elif [ $marks -ge 40 ]; then 
        echo "Grade: E" 
    else 
        echo "Grade: F (Fail)" 
    fi 
} 
 
# Main menu 
while true; do 
    echo "" 
    echo "Arithmetic Functions and Grading System" 
    echo "1. Perform Arithmetic Operations" 
    echo "2. Grading System" 
    echo "3. Exit" 
    echo "Choose an option:" 
    read choice 
 
    case $choice in 
        1) arithmetic_operations ;; 
        2) grading_system ;; 
        3) echo "Exiting..."; exit 0 ;; 
        *) echo "Invalid choice. Please try again." ;; 
    esac 
done 

Write a shell script program for a number to check whether it is  
1. palindrome  
2. prime  
3. generate Fibonacci series  
4. Armstrong, no 
 
#!/bin/bash 
# Function to check if a number is a palindrome 
is_palindrome() { 
    echo "Enter a number to check if it is a palindrome:" 
    read num 
    original=$num 
    reverse=0 
 
    while [ $num -gt 0 ]; do 
        remainder=$((num % 10)) 
        reverse=$((reverse * 10 + remainder)) 
        num=$((num / 10)) 
    done 
 
    if [ $original -eq $reverse ]; then 
        echo "$original is a palindrome." 
    else 
        echo "$original is not a palindrome." 
    fi 
} 
 
# Function to check if a number is prime 
is_prime() { 
    echo "Enter a number to check if it is prime:" 
    read num 
    if [ $num -lt 2 ]; then 
        echo "$num is not a prime number." 
        return 
    fi 
 
    for ((i = 2; i * i <= num; i++)); do 
        if [ $((num % i)) -eq 0 ]; then 
            echo "$num is not a prime number." 
            return 
        fi 
    done 
    echo "$num is a prime number." 
} 
 
# Function to generate Fibonacci series 
generate_fibonacci() { 
    echo "Enter the number of terms for the Fibonacci series:" 
    read terms 
    a=0 
    b=1 
    echo "Fibonacci series up to $terms terms:" 
    for ((i = 0; i < terms; i++)); do 
        echo -n "$a " 
        temp=$((a + b)) 
        a=$b 
        b=$temp 
    done 
    echo 
} 
 
# Function to check if a number is an Armstrong number 
is_armstrong() { 
    echo "Enter a number to check if it is an Armstrong number:" 
    read num 
    original=$num 
    sum=0 
 
    while [ $num -gt 0 ]; do 
        digit=$((num % 10)) 
        sum=$((sum + digit * digit * digit)) 
        num=$((num / 10)) 
    done 
 
    if [ $sum -eq $original ]; then 
        echo "$original is an Armstrong number." 
    else 
        echo "$original is not an Armstrong number." 
    fi 
} 
 
# Main menu 
while true; do 
    echo "" 
    echo "Number Operations Menu" 
    echo "1. Check Palindrome" 
    echo "2. Check Prime" 
    echo "3. Generate Fibonacci Series" 
    echo "4. Check Armstrong" 
    echo "5. Exit" 
    echo "Enter your choice:" 
    read choice 
 
    case $choice in 
        1) is_palindrome ;; 
        2) is_prime ;; 
        3) generate_fibonacci ;; 
        4) is_armstrong ;; 
        5) echo "Exiting..."; exit 0 ;; 
        *) echo "Invalid choice. Please try again." ;; 
    esac 
done


1) Array: Print median of list of numbers. 
         #!/bin/bash 
 
echo "Enter numbers separated by spaces:" 
read -a numbers 
 
sorted=($(echo "${numbers[@]}" | tr ' ' '\n' | sort -n)) 
 
length=${#sorted[@]} 
 
if (( $length % 2 == 0 )); then 
    mid=$((length / 2)) 
    median=$(( (sorted[mid-1] + sorted[mid]) / 2 )) 
else 
    mid=$((length / 2)) 
    median=${sorted[$mid]} 
fi  
echo "Median: $median"                 
Output:  
 
 
2) String: Count the Number of Vowels in a String. 
 
#!/bin/bash 
read -p "Enter a string: " str 
vowel_count=$(echo $str | grep -o -i "[aeiou]" | wc -l) 
echo "Number of vowels: $vowel_count" 
 
Output: 
 
3) Function: Convert given input decimal number to binary number 
 
 #!/bin/bash 
decimal_to_binary() { 
    local decimal=$1 
    binary="" 
     
    while [ $decimal -ne 0 ]; do 
        remainder=$((decimal % 2)) 
        binary="${remainder}${binary}" 
        decimal=$((decimal / 2)) 
    done 
echo $binary 
}    
 
echo "Enter a decimal number:" 
read decimal 
 
binary=$(decimal_to_binary $decimal) 
echo "Binary: $binary"  
Output: 
 
 
 
4) Arithmetic: Calculate the sum of square of first n natural numbers 
#!/bin/bash 
# Sum of squares of first n natural numbers 
 
read -p "Enter the value of n: " n 
sum=0 
 
for (( i=1; i<=n; i++ )) 
do 
  sum=$(( sum + i*i )) 
done 
 
echo "Sum of squares of first $n natural numbers: $sum" 
 
 
5) Command line :-List of integers as command line arguments and 
calculates their average. 
#!/bin/bash 
 
# Check if arguments are passed 
if [ $# -eq 0 ]; then 
    echo "No arguments provided. Please pass integers as arguments." 
    exit 1 
fi 
 
# Calculate the sum of the integers 
sum=0 
for num in "$@"; do 
    sum=$((sum + num)) 
done 
 
# Calculate the average 
average=$(echo "$sum / $#" | bc -l) 
echo "Average: $average" 
Output: 
 
 
6) Executing a linux command in shell :- Take a file name as an argument 
and counts the number of occurrences of a specific word 
provided by the user. 
 
#!/bin/bash 
 
# Input: File name and word to search for 
if [ $# -ne 1 ]; then 
    echo "Usage: $0 <filename>" 
    exit 1 
fi 
 
echo "Enter the word to search for:" 
read word 
 
# Count occurrences of the word 
count=$(grep -o -i "$word" "$1" | wc -l) 
 
echo "The word '$word' occurs $count times in the file '$1'."