#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

// Función para analizar los resultados de nmap
void analyze_nmap_results(const std::string& nmap_output) {
    std::regex pattern("^(\\d+\\.\\d+\\.\\d+\\.\\d+)\\s+.*$"); // Expresión regular para buscar direcciones IP en el resultado de nmap
    std::smatch matches; // Coincidencias de la expresión regular
    std::vector<std::string> ips; // Direcciones IP encontradas

    // Buscar las direcciones IP en el resultado de nmap
    std::string::const_iterator search_start(nmap_output.cbegin());
    while (std::regex_search(search_start, nmap_output.cend(), matches, pattern)) {
        ips.push_back(matches[1].str());
        search_start = matches.suffix().first;
    }

    // Mostrar las direcciones IP encontradas
    std::cout << "Direcciones IP encontradas:" << std::endl;
    for (const auto& ip : ips) {
        std::cout << ip << std::endl;
    }
}

int main() {
    std::string ip_address = "192.168.1.1"; // Dirección IP a escanear
    std::string nmap_command = "nmap " + ip_address; // Comando nmap a ejecutar

    std::cout << "Ejecutando el comando: " << nmap_command << std::endl;

    // Ejecutar el comando de nmap y obtener los resultados
    FILE* stream = popen(nmap_command.c_str(), "r");
    if (stream) {
        std::string nmap_output;
        char buffer[256];
        while (!feof(stream)) {
            if (fgets(buffer, 256, stream) != nullptr) {
                nmap_output += buffer;
            }
        }
        pclose(stream);

        // Analizar los resultados de nmap
        analyze_nmap_results(nmap_output);
    } else {
        std::cerr << "Error al ejecutar el comando de nmap" << std::endl;
    }

    return 0;
}
