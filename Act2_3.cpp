#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct LogEntry {
    std::string ip;
    std::string data;
};

bool compareEntriesByIP(const LogEntry& entry1, const LogEntry& entry2) {
    return entry1.ip < entry2.ip;
}

void readLogFile(std::vector<LogEntry>& logEntries) {
    std::ifstream inputFile("bitacora.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file 'bitacora.txt'\n";
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        LogEntry entry;
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            entry.ip = line.substr(0, pos);
            entry.data = line.substr(pos + 1);
            logEntries.push_back(entry);
        }
    }

    inputFile.close();
}

void writeSortedLogToFile(const std::vector<LogEntry>& logEntries) {
    std::ofstream outputFile("sorted_bitacora.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open file for writing\n";
        return;
    }

    for (const auto& entry : logEntries) {
        outputFile << entry.ip << " " << entry.data << "\n";
    }

    outputFile.close();
}

int main() {
    std::vector<LogEntry> logEntries;
    readLogFile(logEntries);

    // Sort log entries by IP
    std::sort(logEntries.begin(), logEntries.end(), compareEntriesByIP);

    writeSortedLogToFile(logEntries);

    // Ask user for IP range
    std::string startIp, endIp;
    std::cout << "Enter start IP: ";
    std::cin >> startIp;
    std::cout << "Enter end IP: ";
    std::cin >> endIp;

    // Display records for the specified IP range
    for (const auto& entry : logEntries) {
        if (entry.ip >= startIp && entry.ip <= endIp) {
            std::cout << entry.ip << " " << entry.data << "\n";
        }
    }

    return 0;
}
