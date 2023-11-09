# Scripts

## Execute entire progress with documents opened

```ps1
.\runner.ps1 -spsd -odw -p hw3
```

## Execute Normally

```ps1
.\runner.ps1 -p hw3
```

## Options

```
Usage: runner.ps1 -p <project> [-h] [-nc] [-spsd] [-odw]
  -p <program> : project to run
  -h           : help
  -nc          : no cleaning
  -spsd        : start python simple http server for documentation
  -odw         : open documentation in web browser (firefox)
```