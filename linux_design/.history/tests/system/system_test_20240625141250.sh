#!/bin/bash

# Simple system test using curl
echo "Testing HTTP request"
curl -x http://localhost:8080 http://example.com

echo "Testing HTTPS request"
curl -x https://localhost:8080 https://example.com --insecure
