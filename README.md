# Hand Gesture Vision

Proyecto de visión por computadora en C++ para detectar gestos de la mano y controlar un modelo 3D.

## Objetivo

Crear un sistema que detecte manos usando OpenCV y reconozca gestos.

## Roadmap

- [ ] Captura de webcam
- [ ] Detección de piel
- [ ] Contornos
- [ ] Detección de dedos
- [ ] Reconocimiento de gestos
- [ ] Control de modelo 3D

---

# Después de esto vendrá lo interesante

Los siguientes pasos son los que **hacen el sistema realmente poderoso**:

### 1️⃣ Detectar la mano real
convex hull + defects

### 2️⃣ Contar dedos
finger counting

### 3️⃣ Detectar gestos
ejemplo:

| gesto | acción |
|------|------|
| 1 dedo | mover |
| 2 dedos | rotar |
| puño | detener |

### 4️⃣ Controlar un modelo 3D
con:

- **OpenGL**
- **Blender API**
- **Three.js (si usas web)**

---

💡 Si quieres, en el siguiente paso te enseño algo **MUY importante**:

**cómo detectar dedos correctamente (convex hull + convexity defects)**

Eso es lo que usan muchos sistemas de **hand tracking clásico antes de usar IA**.  
Y te va a volar la cabeza cuando lo veas 🤯.