FROM ubuntu:25.10

# Install necessary build tools and a timeout utility
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
        build-essential \
        nasm \
        && apt-get clean && rm -rf /var/lib/apt/lists/*

# Create a non-root user for security
RUN useradd -m runner
USER runner
WORKDIR /home/runner

# Copy the source code
COPY --chown=runner:runner src ./src
COPY source_code.ffo ./

# Optional: precompile the compiler if it's part of your system
RUN g++ ./src/main.cpp -o ./program

# Default command: compile and run submitted code with timeout
CMD ["timeout 5s", "bash -c", "./program ./source_code.ffo"]
