/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jordi
 *
 * Created on September 13, 2017, 4:42 PM
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "zutil.h"
#include "zindex.h"
#include "CStringTools.h"
#include "CTFasta.h"
#include "File.h"

void help(std::string name) {
    std::cerr << "indexingtFasta\n"
            << "Usage: ./indexingtFasta -i file(.gz)\n"
            << "Options:\n"
            << "\t-h\t\tHelp and exit\n"
            << "\t-i\t\ttFasta or Weights file (compressed or uncompressed) to index\n"
            << std::endl;
}

int main(int argc, char** argv) {

    /////////////////////////////
    // Argumentos del programa //
    /////////////////////////////

    std::string tfastafile;
    std::string outtfasta;
    std::string indexname;

    char tmp;
    if (argc == 1) {
        help(argv[0]);
        exit(1);
    }

    while ((tmp = getopt(argc, argv, "hi:")) != -1) {
        switch (tmp) {
            case 'h':
                help(argv[0]);
                break;
            case 'i':
                tfastafile = std::string(optarg);
                break;
        }
    }

    if (tfastafile == "") {
        // Si no se da ninguna lista de tFastas en el comando
        std::cout << std::endl;
        std::cout << "Error:" << std::endl;
        std::cout << "\ttFasta not defined" << std::endl;
        std::cout << std::endl;
        return 1;
    }

    std::cout << std::endl;
    std::cout << "tFasta to index: " << tfastafile << std::endl;
    std::vector<std::string> tfastaname_vector = CStringTools::split(tfastafile, '.');
    if (tfastaname_vector[tfastaname_vector.size()-1] == "gz") {
        for (int i = 0; i < tfastaname_vector.size() - 1; i++) {
            outtfasta = outtfasta + tfastaname_vector[i] + ".";
        }
        outtfasta = outtfasta + "indexed.gz";
    } else {
        outtfasta = tfastafile + ".indexed.gz";
    }
    indexname = tfastafile + ".index";
    std::cout << "tFasta indexed and index: " << outtfasta << " & " << indexname << std::endl;
    std::cout << std::endl;

    CTFasta tfasta(tfastafile);
    CTFasta out_tfasta(outtfasta);

    std::string line;

    // Abrir el tFasta output para escribir en él
    if (out_tfasta.openWriteFile()) {
        // Abrir los 2 tFasta que queremos unir
        if (tfasta.openReadFile()) {
            // Siempre que no lleguemos al final de ambos archivos:
            while (!tfasta.endFile()) {
                line = tfasta.readLine();
                out_tfasta.writeFile(line + '\n');
            }
            tfasta.closeFile();
        }
        out_tfasta.closeFile();
    }

    return 0;
}
