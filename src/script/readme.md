# Scripts

## Development Steps

Use project "hw3" for example.

1. Code completion: ```./runner.ps1 -p hw3``` or ```./runner.ps1 -p hw3 -nc```
2. Evaluate documentation:
   1. Start python http server: ```./runner.ps1 -p hw3 -gdoc -spsd```
   2. Open document on http server: ```./runner.ps1 -p hw3 -gdoc -spsd -odw```
3. Deploy documentation to github pages: ```./runner.ps1 -p hw3 -dgp```
4. Full pipeline: ```./runner.ps1 -p hw3 -gdoc -spsd -odw -dgp```

## Options

```
Usage: runner.ps1 -p <project> [-h] [-nc] [-gdoc] [-spsd] [-odw] [-dgp]
  -p <program> : project to run
  -h           : help
  -nc          : no cleaning
  -gdoc        : generate documentation
  -spsd        : start python simple http server for documentation
  -odw         : open documentation in web browser (firefox)
  -dgp         : deploy to github pages (https://belongtothenight.github.io)
```