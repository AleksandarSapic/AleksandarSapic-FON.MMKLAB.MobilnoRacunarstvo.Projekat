## Overview

This school project focuses on building an IoT-based security system for monitoring house entry. The system checks if the correct access code is entered; if incorrect, it sends information to a server for logging and further action.

## Project Structure

.<br />
├── firmware/ # Firmware code for IoT device <br />
├── server/ # Server-side application code <br />
└── schema.png # Schema for IoT device <br />

### `firmware/`

The firmware/ directory contains the code for the IoT device responsible for monitoring house entry and validating access codes.

### `server/`

The server/ directory houses the server-side application responsible for receiving data from the IoT device, logging events, and processing access attempts.

### `server/app.js`

The app.js file serves as the main entry point for the server-side application, containing API routes and middleware configurations.

## Project Purpose

This project aims to develop a secure IoT-based security system for monitoring house entry. It demonstrates real-time event handling, access validation, and server-side logging of security events.

## Functionality

The IoT device continuously monitors house entry point. When an access code is entered:
- If the code is correct, the system grants access.
- If the code is incorrect, the IoT device sends information to the server.

The server logs these events, providing a record of access attempts and ensuring security monitoring.
