# Scripts

Note: This likely isn't the lastest content, visit [PRML_Code repository](https://github.com/belongtothenight/PRML_Code) for up-to-date content.

## Development Steps

Use project "hw3" for example.

1. Code completion: ```./runner.ps1 -p hw3``` or ```./runner.ps1 -p hw3 -nc```
2. Evaluate documentation:
   1. Start python http server: ```./runner.ps1 -p hw3 -spsd```
   2. Open document on http server: ```./runner.ps1 -p hw3 -spsd -odw```
3. Deploy documentation to github pages: ```./runner.ps1 -p hw3 -dgp```

## Options

```
Usage: runner.ps1 -p <project> [-h] [-nc] [-spsd] [-odw]
  -p <program> : project to run
  -h           : help
  -nc          : no cleaning
  -spsd        : start python simple http server for documentation
  -odw         : open documentation in web browser (firefox)
  -dgp         : deploy to github pages (https://belongtothenight.github.io)
```