# CallTrackApp2

A C++ CRUD application developed for a Data Structures course (2023), featuring a custom implementation of a doubly linked list with a dummy head node.

## Features

- CRUD operations for managing call records
- Custom doubly linked list implementation
- Object-oriented design with domain-specific classes:
  - Agent
  - Call
  - Schedule
  - Date & Time
- GUI built with raygui
- File-based data storage for testing

## Data Structures

The core of the application is a manually implemented doubly linked list using a dummy head node. This design simplifies insertion and deletion operations by avoiding edge cases.

## Technologies

- C++
- raygui (GUI library)

## 📁 Project Structure

- `CallTrackApp` – main application logic
- `CallList` – doubly linked list implementation
- `CallNode` – list node
- `models/` – domain classes
- `resources/` – assets (logo)
- `data/` – test data

## Notes

This project was originally developed in November 2023 as part of a university course.