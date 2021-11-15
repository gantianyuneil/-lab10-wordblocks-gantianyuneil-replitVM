Word Blocks
===

In this lab you will use the things you have learned in class and from
the recent labs and homeworks to pack a data buffer with words from an
input string.

Requirements
---

You must implement the following two functions in `wordblocks.c`:

`int pack_chunk(char *word, void *output)`

`int wordblocks(char *input[], void *output);`

### `pack_chunk`
This function must encode a provided word and length into a block and
return the total number of bytes encoded into the buffer `output`. The
word to pack is provided as a NUL-terminated string `word`.

Each block is a 16-bit `short` containing the number of bytes in the
encoded word, followed by the bytes of the word.  A block containing
the word "Hello" would have the following form:

| short | character data          |
|-------|-------------------------|
|     5 | 'H', 'e', 'l', 'l', 'o' |

Note that there is **No terminating NUL byte** on the word Hello in the chunk!

### `wordblocks`

This function must encode every "word" in the provided _array of strings_
`input` as a _block_ in the buffer `output`, and return the total number
of bytes encoded into the buffer `output`.

Each word is given as a NUL-terminated string in the `input`
array. The length of `input` is not explicitly given.  Instead, the
end of the array is marked by the pointer NULL.  (You may find this
format familiar, as it is the exact format command line arguments are
passed in via `argv`.)  Words may have a length of zero, in which case
the string will be an empty string.

The end of the output array is encoded as a `short` length of `-1`.

The following sentence and example encoding should help clarify this:

Input: `{"I", "like", "it.", "", "I'll", "take", "it."}`

Output:

| 1 | I | 4 | like | 3 | it. | 0 | 4 | I'll | 4 | take | 3 | it. | -1 |

(The number preceding each chunk is a 16-bit `short` integer.) This
output has a total length of 35 (8 2-byte short integers plus 19
encoded word characters), and thus `wordblocks()` would return 35.

Testing and Example Output
---

Typing `make` will build the program `testblocks`, which takes _a
series of arguments_ on the command line, calls `wordblocks()` on
those arguments, and writes the result to the file `words.out`.  Note
that it _depends on the return value of `wordblocks()` being correct_,
and that an incorrect return value may lead to a crash or corrupt
output.

You can test against an input _of your choice_ by observing the
encoded output of a sentence that you submit to `testblocks` using a
command such as:

`od -t x1 -a words.out`

This command will print both the hex value of every byte in the file
`words.out` as well as its ASCII equivalent character.  For example,
encoding the sentence "Shop smart, shop S-Mart!" would work as:

```bash
$ ./testblocks Shop smart, shop S-Mart!
$ od -t x1 -a words.out
0000000  04  00  53  68  6f  70  06  00  73  6d  61  72  74  2c  04  00
        eot nul   S   h   o   p ack nul   s   m   a   r   t   , eot nul
0000020  73  68  6f  70  07  00  53  2d  4d  61  72  74  21  ff  ff
          s   h   o   p bel nul   S   -   M   a   r   t   ! del del
0000037
```

Note that each `short` integer is represented by two bytes (the second
of which is 0 in each of these, because no word is longer than 255
characters), followed by its respective word, and that the file ends in
`0xffff`, which we know is 2's complement for -1.

Empty words can be expressed on the command line as
`""`. Additionally, characters interpreted by the shell must be
escaped with a backslash (`\`). For example, to test the input
`{"I", "like", "it.", "", "I'll", "take", "it."}` you would run:

```
$ ./testblocks I like it. "" I\'ll take it.
```

Hints and Discussion
---

You should start by implementing `pack_chunk`, and call your
implementation of `pack_chunk` from `wordblocks`. Once correctly
implemented, `pack_chunk` will do most of the work.

Since the length of the input array is not explicitly given, you will
need to test for NULL as an element of the array to find the end.

Do not forget to include the length fields or the terminating -1 in
the count of bytes written.

The `input` and `output` arrays are allocated for you by the calling
code.  Therefore, you need not dynamically allocate memory using
`malloc` or `calloc`.

Submission
---

Submit only the file `wordblocks.c` to Autograder.

Grading
---

Points will be awarded as follows:

`pack_chunk`
 * 1 pts: The empty string is encoded correctly (as a single block of size 0)
 * 1 pts: A single word is encoded correctly

`wordblocks`
 * 1 pts: A single word is encoded correctly
 * 2 pts: Sentences with multiple words and empty words are encoded correctly


Crashes in the Autograder _almost certainly indicate bugs in your
program_.  The Autograder scripts try to defend themselves against
erroneous implementations, but an incorrect implementation can still
cause crashes.
