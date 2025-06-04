FROM debian:bookworm-slim

# Install minimal runtime dependencies (if needed)
RUN apt-get update && apt-get install -y \
    coreutils \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Create non-root user
RUN useradd -m runner
USER runner
WORKDIR /home/runner

# Copy prebuilt compiler binary
COPY --chown=runner:runner build/sacompiler /usr/local/bin/sacompiler

# Add wrapper script
COPY --chown=runner:runner run.sh /usr/local/bin/run-code
RUN chmod +x /usr/local/bin/run-code

ENTRYPOINT ["/usr/local/bin/run-code"]
