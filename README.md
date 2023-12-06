# 🏥 PacVac Management Program

PacVac is a C-based program designed to manage a vaccination site, allowing administrators to manage their patient database and vaccination queues utilizing Data Abstract Types (TAD) such as Lists, Queues, and Binary Trees. It provides a comprehensive structure for patient management and vaccine administration.

## 🌟 Features

 - 📚 Patient Database Management (implemented using a Binary Tree)
   - ➕ Add new patients.
   - 📋 List all patients.
   - ❌ Remove a patient.

  - 💉 Vaccination Site Management (utilizing Queues and Lists)
    - 🧑‍🔬 Create a vaccination queue.
    - 💉 Administer vaccines.

## 🛠 Compilation

```
gcc -o PacVac main.c vacunodromo.c TADs/cola.c TADs/lista.c TADs/abb.c -Wall
```

## 🚀 Usage

Run the compiled program:
```
./PacVac
```

On launching, you'll be greeted with the main menu:

```
Bienvenido al programa de gestión PacVac
A. Gestión de la base de datos
B. Gestión del vacunódromo
S. Salir
Seleccione una opción:
```

## 🤝 Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
