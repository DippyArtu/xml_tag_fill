# xml_tag_fill
A program to populate an .xml file with tags

At the moment, it's tailored to a specific task:



find all mentions of a _`\<barcode>`_ tag and insert corresponding picture links in the format
     `https://storage.cloud.google.com/fotobank1/***LINK***?hl=ru` with a `<picture>` tag after the barcode.
     
Program will read data from the input file, looking for the barcode IDs
It will then find corresponding link IDs in the second file given as an argumant and translate them into the link form
Then, it will populate the file with those links, including the `<picture>` tag, after the corresponding `<barcode>` tag.



For example:

A string `<barcode>88063</barcode>` is found, where `88063` is a unique barcode ID.

The program will look for a `88063.jpg` string in the `LINK_IDs` file, given as an argument (each ID should be on a new line)

It will then a generate link in format `<picture>https://storage.cloud.google.com/fotobank1/88063?hl=ru</picture>` and insert it after the `</barcode>` tag

The result would be `<barcode>88063</barcode><picture>https://storage.cloud.google.com/fotobank1/88063?hl=ru</picture>`
     
A new file populated with links will be generated in the working directory.



**USAGE:**

Compile: `$make`

`$./xml_tag_fill FILE_TO_POPULATE LINK_IDs`

All input files must be in the working directory.



Even though the functionality of the program is very limited at the moment, it can be used in different ways by changing 
tag names and link types in the source code.

I also plan to make a fully functional program later.