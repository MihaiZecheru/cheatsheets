Cheatsheets CLI
----------------------------

Note: Adding this program to PATH is highly recommended.
Download the compiled `.exe` file [here](https://github.com/MihaiZecheru/cheatsheets/edit/main/README.md)

This program was made with the intent of providing quick answers to common programming problems in order
to save you time that would have instead been spent on tedious googling. This cheatsheet CLI will return
`cheatsheets` as the results to its queries, which are created through the given command-line arguments.
This program's main usage is a `--lang` flag and a query, for example `how to append to array --javascript`

If you're in the mood to learn something new, you can use the `:random` tag to view a random cheatsheet, or
you can start learning another language entirely in the command line by passing a `--lang` flag and the `:learn`
tag to the CLI. If you don't care for this, there are two `search operators` you can use to refine your results.
To exclude certain words from the results, prefix those words with a minus sign (-). To retrieve multiple different
cheatsheets, all containing specific keyword(s), prefix those keyword(s) with a tilda (~).

**Usages:**

        c <command> [--lang]
        c <--lang> :learn
        c :random

**Examples:**

        c sum of list --python
        c remove first item from array --javascript
        c use curl --shell
        c ls --cmd

`To exclude certain words from results, prefix the word with a minus sign (-)`

**Examples:**

        c --python multiply matrices -numpy
        c hello world --cpp -printf

`Note: to find results containing certain keywords, prefix the keywords with a tilda (~)`

**Examples:**

        c --js ~array
        c ~inheritance ~classes --python
