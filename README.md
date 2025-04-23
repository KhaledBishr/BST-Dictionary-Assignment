# BST Dictionary - Spell Checker 📘🌳

This project implements a **spell-checking system** using a **Binary Search Tree (BST)** in C. It is developed as part of the Data Structures (CSE127) course at Alexandria University, Spring 2024.

## 🧠 Project Description

The program reads a dictionary file containing one word per line and constructs a BST from it. Upon loading, it prints:
- 📏 The size (number of nodes) of the BST
- 🌲 The height of the BST

### 💬 How It Works

1. Load the dictionary from file into a BST.
2. Prompt the user to input a sentence.
3. For each word in the sentence:
   - ✅ If it exists in the BST, print it is correct.
   - ❌ If it does not exist:
     - Suggest three possible corrections:
       - The word in the **last node visited** before concluding it's not found.
       - The **inorder predecessor** of that node.
       - The **inorder successor** of that node.

String comparisons are **case-insensitive** using the `strcasecmp` function.

## 🛠️ How to Run

1. Compile the code:
   ```bash
   gcc -o spell_checker main.c
   ```

2. Run the program:
   ```bash
   ./spell_checker
   ```

3. Follow the on-screen prompts to input your sentence and receive feedback.

## 📁 File Structure

```
📦bst-dictionary-spellchecker
 ┣ 📄main.c              # All source code in one file
 ┣ 📄dictionary.txt      # Word list for BST (one word per line)
 ┣ 📄README.md           # This file
```

## 🧪 Sample Run

```
BST Size: 25143
BST Height: 19
Enter a sentence: hello wurld
hello is correct.
wurld is incorrect. Suggestions:
  → world (last node visited)
  → worry (inorder predecessor)
  → wound (inorder successor)
```

