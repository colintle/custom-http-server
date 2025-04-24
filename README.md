# Custom HTTP Server

A lightweight, C++-based HTTP server built from scratch, supporting essential HTTP methods and serving static files. Designed for educational purposes and to provide a foundational understanding of HTTP server mechanics.

## Features

- **HTTP Methods**: Supports `GET` and `POST` requests.
- **Static File Serving**: Serves files from a specified root directory.
- **Modular Design**: Organized codebase with clear separation between headers, source files, and frontend assets.
- **Makefile Support**: Simplified build process using a provided Makefile.

## Project Structure

```
custom-http-server/
├── frontend/       # Contains static assets (HTML, CSS, JS)
├── include/        # Header files defining server classes and interfaces
├── src/            # Implementation of server functionalities
├── Makefile        # Build instructions
└── .gitignore      # Git ignore rules
```

## Getting Started

### Prerequisites

- **Compiler**: A C++ compiler supporting C++11 or later.
- **Build Tools**: `make` utility installed on your system.

### Build Instructions

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/colintle/custom-http-server.git
   cd custom-http-server
   ```

2. **Compile the Server**:

   ```bash
   make
   ```

3. **Run the Server**:

   ```bash
   ./server
   ```

   By default, the server listens on port `8080`. You can access it by navigating to `http://localhost:8080` in your web browser.

## Configuration

Currently, the server uses default settings:

- **Port**: `8080`
- **Static HTML Directory**: `./frontend/`
