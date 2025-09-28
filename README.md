# 🚀 Webserv42 — Servidor HTTP/1.1 en C++98

Proyecto del currículum de 42 que consiste en implementar un servidor web HTTP/1.1 desde cero, en C++98, sin frameworks externos. El objetivo es comprender a nivel bajo cómo funciona la web: sockets, parsing de peticiones, multiplexación de E/S, rutas, CGI y gestión de archivos. 🌐

---

## ✨ Objetivos del proyecto

- Implementar un servidor HTTP/1.1 con soporte para múltiples clientes.
- Servir contenido estático (HTML, CSS, JS, imágenes).
- Soportar métodos HTTP: GET, POST y DELETE.
- Gestionar rutas con configuración por “servidor” y “location”.
- Ejecutar CGI (por ejemplo, scripts en Bash o Python).
- Permitir subida de ficheros vía multipart/form-data.
- Ofrecer autoindex y páginas de error personalizadas.
- Usar E/S no bloqueante y multiplexación (poll).

---

## ⚙️ Características técnicas

- HTTP/1.1 con parsing manual de cabeceras y body.
- Sockets no bloqueantes + poll(2) para manejar múltiples conexiones.
- Timeouts de conexión y cierre ordenado.
- Rutas configurables: root, index, métodos permitidos, autoindex.
- CGI con variables de entorno estándar (REQUEST_METHOD, CONTENT_LENGTH, QUERY_STRING, etc.).
- Límites de tamaño de body (413 Payload Too Large).
- Respuestas de error dedicadas (404, 405, 500, …).

---

## 🗂️ Estructura del repositorio

```
webserv-42/
├── include/            # Headers del proyecto
├── src/                # Código fuente C++
├── assets/             # Recursos estáticos (bootstrap, css, js, imágenes, fuentes)
│   ├── bootstrap/
│   ├── css/
│   ├── fonts/
│   ├── img/
│   └── js/
├── configs/            # Archivos de configuración (.conf)
├── cgi/                # Scripts y páginas de prueba CGI
├── upload/             # Carpeta destino de subidas y tests
├── delete/             # Página de prueba para DELETE
├── templates/          # Plantillas (autoindex, errores, etc.)
└── ...                 # Archivos de demo en la raíz (index.html, etc.)
```

Nota: si tu repositorio incluye `configs/`, usa ahí tus `.conf`. Si no, incluye la ruta al fichero de configuración que uses al ejecutar.

---

## 🏃 Compilación y ejecución

```sh
make
./webserv path/a/tu_config.conf
```

Navega a:
```
http://localhost:8080/
```

### 🧪 Demos en localhost
- /                 Home con enlaces a todas las pruebas
- /configs/         Autoindex de configuración
- /upload.html      Form de subida vía fetch (POST multipart → /upload)
- /multipart.html   Form de subida clásico (POST multipart → /upload)
- /delete/test_delete.html   Prueba de DELETE
- /cgi/post_cgi.html         Demo de POST a CGI
- /cgi.sh y /cgi.py          CGIs simples de prueba

---

## 🧩 Configuración (visión general)

- Estilo inspirado en Nginx: bloques de servidor y locations.
- Parámetros típicos por servidor:
  - listen (puerto), server_name, root, index, error_page.
- Parámetros por location:
  - métodos permitidos (GET/POST/DELETE), autoindex on/off,
  - rutas de subida de archivos, mapeo CGI (extensión → intérprete),
  - redirecciones y páginas personalizadas.

Consulta tu `default.conf` para la sintaxis exacta implementada en este proyecto.

---

## 🔁 Flujo de petición

1. Aceptación de conexión (socket no bloqueante).
2. Lectura de cabeceras y cuerpo (según Content-Length/transfer).
3. Enrutado por “server” y “location”.
4. Manejo según método:
   - GET: archivo estático o autoindex.
   - POST: subida multipart/form-data o ejecución de CGI.
   - DELETE: eliminación de recursos permitidos.
5. Generación de respuesta (status, headers, body).
6. Envío y cierre/keep-alive.

---

## 🏁 Lo que se aprende

- Fundamentos de servidores HTTP: parsing, estados y respuestas.
- Sockets, no-bloqueo y multiplexación con poll(2).
- Diseño modular de un servidor (parsers, router, response builder, CGI).
- Seguridad básica: restricciones de métodos, límites de tamaño, paths.
- Integración de CGI y variables de entorno.
- Depuración con herramientas como curl y logs de trazas.

---

## 📚 Recursos

- RFC 2616 — HTTP/1.1
- CGI — Common Gateway Interface (W3C)
- Man pages: socket(2), bind(2), listen(2), accept(2), poll(2), fcntl(2)