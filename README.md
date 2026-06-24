## Build

Configure the project:

```bash
cmake -B build
```

Build the project:

```bash
cmake --build build
```

Or build using all available CPU cores:

```bash
cmake --build build --parallel
```

## Run

Run the generated executable:

```bash
./build/<executable_name>
```

Replace `<executable_name>` with the target name defined in `add_executable()`.
