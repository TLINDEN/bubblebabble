# bubblebabble
Encode to Bubble Babble

## Intro

OpenSSH'  ssh-keygen  has  an  implementation  of  the  bubble  babble
encoding for  key fingerprints. This  is a little wrapper  around that
function so you can encode anything to bubble babble.

## Compile and Install

    gcc -g bubblebabble.c -o bubblebabble
    sudo install -o root -g wheel bubblebabble /usr/local/bin/

## Usage

    % sha256 -q filename | bubblebabble
    xevef-lotek-gonok-dataf-linif-gesek-konof-humuk-devyf-do[..]

## Copyright + Author

Copyright (c) 2017 T.v.Dein. All rights reserved.

fingerprint_bubblebabble(): 

Copyright (c) 2000, 2001 Markus Friedl.  All rights reserved.
Copyright (c) 2008 Alexander von Gernler.  All rights reserved.
Copyright (c) 2010,2011 Damien Miller.  All rights reserved.
