# Restaurant_table_reservation_CLI_2024_C


# 🍽️ Restaurant Table Reservation System

A C-based command-line application for managing restaurant table reservations, supporting automated table assignments, real-time availability tracking, and persistent storage. Designed for restaurants that handle reservations for tables of varying capacities (2, 4, 6, and 8 people).

---

## 🚀 Features

### ✅ Reservation Management

* Create new reservations with:

  * Customer name & phone
  * Party size
  * Date & hour (up to 2 years ahead)
  * Allergies & dietary preferences
* Smart table allocation based on group size (supports table combination for large groups)
* Cancel or modify the most recent reservation

### 🧠 Table Availability Tracking

* Uses a **3D availability matrix** (`tables × 732 days × 24 hours`)
* View:

  * All reservations
  * Available tables for a specific date and hour
  * Bookings for a specific table

### 💾 Data Persistence

* Reservation details saved in `booking.txt` (CSV-like)
* Table availability stored in `2darray.txt`

---

## ⚙️ Usage

### 🛠 Prerequisites

* GCC compiler
* Unix/Linux-based system (for `unistd.h` compatibility)

### 📦 Compilation & Execution

```bash
gcc reservation_system.c -o reservation_system
./reservation_system
```

---

## 📋 Menu Options

1. **Make Reservation**

   * Input: Name, Phone, Party Size, Date (0–731), Hour (0–23), Allergies, Dietary Needs
   * Output: Assigned tables or unavailability message

2. **Print Bookings**

   * All Bookings: Lists all reservations
   * By Date/Hour: Shows available tables
   * By Table: Lists bookings for a specific table

3. **Change Reservation**

   * Cancel or modify the **most recent** booking

4. **Save Reservations**

   * Manually save all changes to disk

5. **Exit**

   * Automatically saves data before quitting

---

## 🧪 Example Workflow

### 1. Make Reservation

```text
→ Input: "John Doe", "1234567890", 5 people, Day 10, Hour 14, "None", "Vegetarian"
→ Output: "Assigned Tables: 14, 15"
```

### 2. View Bookings

```text
→ Option: Print All Bookings
→ Output: John Doe, 1234567890, 5 people, Day 10, Hour 14, Tables 14-15
```

### 3. Cancel Reservation

```text
→ Option: Delete Last Reservation
→ Output: Last booking canceled.
```

---

## 🗂 File Structure

| File Name              | Description                                                 |
| ---------------------- | ----------------------------------------------------------- |
| `reservation_system.c` | Main source code                                            |
| `booking.txt`          | Stores all bookings in human-readable format                |
| `2darray.txt`          | Binary-like format for internal table availability tracking |

---

## 📐 Design Notes

* **Table Structure:** Grouped by size — 2, 4, 6, and 8 seats
* **Table Allocation:** Rounds up odd group sizes (e.g., 5 → 6) and combines tables if needed
* **Edge Case Handling:** Reverts booking if suitable tables aren't available

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

