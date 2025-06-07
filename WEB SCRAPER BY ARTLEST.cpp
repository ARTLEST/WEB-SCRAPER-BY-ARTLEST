#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

// Real web scraping function using curl
string realWebScraping(const string& url) {
    string filename = "temp_download.html";
    string command = "curl -s \"" + url + "\" -o " + filename;
    
    cout << "Attempting real web scraping..." << endl;
    
    // Try to execute curl command
    int result = system(command.c_str());
    
    if (result == 0) {
        // Successfully downloaded, read the file
        ifstream file(filename.c_str());
        if (file) {
            string content;
            string line;
            while (getline(file, line)) {
                content += line + "\n";
            }
            file.close();
            
            // Clean up temp file
            remove(filename.c_str());
            
            if (!content.empty()) {
                cout << "Real web scraping successful!" << endl;
                return content;
            }
        }
    }
    
    cout << "Real web scraping failed. Using simulated content." << endl;
    return "";
}

// Fallback simulated content function
string getSimulatedContent(const string& url) {
    if (url.find("example.com") != string::npos) {
        return "<!DOCTYPE html>\n<html>\n<head>\n<title>Example Domain</title>\n</head>\n<body>\n<h1>Example Domain</h1>\n<p>This domain is for use in illustrative examples.</p>\n<p><a href=\"https://www.iana.org/domains/example\">More information...</a></p>\n</body>\n</html>";
    }
    else if (url.find("test") != string::npos || url.find("demo") != string::npos) {
        return "<!DOCTYPE html>\n<html>\n<head>\n<title>Test Page</title>\n</head>\n<body>\n<h1>Test Website</h1>\n<p>This is a test webpage for scraping.</p>\n<p>Contact: <a href=\"mailto:test@example.com\">test@example.com</a></p>\n<div>Sample content with multiple elements.</div>\n</body>\n</html>";
    }
    else {
        return "<!DOCTYPE html>\n<html>\n<head>\n<title>Sample Page</title>\n</head>\n<body>\n<h1>Web Scraper Demo</h1>\n<p>This is sample HTML content.</p>\n<p>URL requested: " + url + "</p>\n<a href=\"#\">Sample Link 1</a>\n<a href=\"#\">Sample Link 2</a>\n</body>\n</html>";
    }
}

// Main download function that tries real scraping first
string downloadWebpage(const string& url) {
    // First try real web scraping
    string content = realWebScraping(url);
    
    // If real scraping failed, use simulated content
    if (content.empty()) {
        cout << "Using simulated content for demonstration." << endl;
        content = getSimulatedContent(url);
    }
    
    return content;
}

int main() {
    // Introduction
    cout << "Real Web Content Scraper" << endl;
    cout << "Created by ARTLEST" << endl;
    cout << "Features: Real + Simulated Scraping" << endl;
    cout << "------------------------------------" << endl;
    
    // Get URL from user
    string url;
    cout << "Enter website URL to scrape: ";
    getline(cin, url);
    
    // Handle empty input
    if (url.empty()) {
        url = "https://example.com";
        cout << "Using default URL: " << url << endl;
    }
    
    cout << "\nProcessing webpage..." << endl;
    
    // Download webpage content
    string content = downloadWebpage(url);
    
    // Save to file
    string filename = "scraped_page.html";
    ofstream outFile(filename.c_str());
    
    if (!outFile) {
        cout << "Error: Unable to create output file." << endl;
        return 1;
    }
    
    outFile << content;
    outFile.close();
    
    cout << "Content saved to: " << filename << endl;
    
    // Display content
    cout << "\n--- WEBPAGE CONTENT ---" << endl;
    
    istringstream contentStream(content);
    string line;
    int lineCount = 0;
    
    while (getline(contentStream, line) && lineCount < 15) {
        cout << line << endl;
        lineCount++;
    }
    
    if (lineCount >= 15) {
        cout << "\n(Showing first 15 lines only)" << endl;
    }
    
    // Analyze content
    cout << "\n--- ANALYSIS RESULTS ---" << endl;
    
    // Count basic elements
    int totalChars = content.length();
    int htmlTags = 0;
    int links = 0;
    
    // Count HTML tags (opening brackets)
    for (int i = 0; i < totalChars; i++) {
        if (content[i] == '<') {
            htmlTags++;
        }
    }
    
    // Count links
    size_t pos = 0;
    while ((pos = content.find("href=", pos)) != string::npos) {
        links++;
        pos += 5;
    }
    
    // Also check for http links
    pos = 0;
    while ((pos = content.find("http", pos)) != string::npos) {
        if (pos == 0 || !isalnum(content[pos-1])) {
            links++;
        }
        pos += 4;
    }
    
    // Display results
    cout << "Total characters: " << totalChars << endl;
    cout << "HTML tags found: " << htmlTags << endl;
    cout << "Links detected: " << links << endl;
    cout << "Content saved to: " << filename << endl;
    
    cout << "\nScraping completed successfully." << endl;
    cout << "- ARTLEST" << endl;
    
    return 0;
}