# Student Management System

Welcome to the **Student Management System**, a console-based application developed as a group project for the **Introduction to Computer Science II** course. This system provides functionalities for managing students, staff, courses, semesters, and academic records in a school environment. It supports two primary user roles: **Staff Members** and **Students**, with features ranging from user authentication to grade management and data export/import via CSV files.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Directory Structure](#directory-structure)

## Project Overview
The Student Management System is designed to streamline academic administration tasks. Staff members can create school years, semesters, courses, and classes, manage student enrollments, and handle grades. Students can view their profiles, course lists, and scores once published by staff. The system uses a file-based database (CSV and text files) to store and retrieve data, with a focus on modularity and linked-list-based data structures.

This project was developed by a team of three students as part of the coursework for **Introduction to Computer Science II**, emphasizing object-oriented programming, file I/O, and data management.

## Features
### Staff Features
- **User Authentication**: Login and logout functionality.
- **Profile Management**: View and update personal information, change password.
- **Academic Structure Management**:
  - Create new school years and semesters.
  - Add classes for first-year students.
  - Add courses to semesters.
- **Student Management**:
  - Add students to classes manually or via CSV.
  - Enroll/remove students in courses.
  - Update course information.
- **Grade Management**:
  - Import/export student grades via CSV.
  - View and update scoreboards for courses and classes.
  - Publish scores for student access.
- **Data Viewing**:
  - View lists of classes, students, courses, and scoreboards.

### Student Features
- **Profile Access**: View personal information.
- **Course Information**: View enrolled courses for the current semester.
- **Score Viewing**: Access published scoreboards.

### General Features
- Data persistence using CSV and text files.
- Input validation and error handling.
- Support for linked-list-based data structures.

## Directory Structure
The project organizes data into three main folders:
- **User/**:
  - `Published.txt`: Indicates if scores are published.
  - `SchoolYear.txt`: Stores school years and semesters.
  - `staffMember.csv`: Staff information.
  - `student.csv`: Student information.
- **Course/**:
  - `<CourseID>Score.csv`: Stores course grades (e.g., `123Score.csv`).
  - `<CourseID>Students.csv`: Lists students enrolled in a course (e.g., `123Students.csv`).
  - `Course.csv`: Details of all courses, including semester and year.
- **Class/**:
  - `<ClassName>.csv`: Lists student IDs in a class (e.g., `20APCS1.csv`).
  - `Class.txt`: Stores class names.
