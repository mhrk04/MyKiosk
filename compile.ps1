$sourceFiles = @("checkDatabase.c", "createKioskStock.c", "dailyUpdate.c","displayKioskDatabase.c","menu.c","sellItem.c")
$outputFiles = @("bin\checkDatabase.exe", "bin\createKioskStock.exe", "bin\dailyUpdate.exe","bin\displayKioskDatabase.exe","bin\menu.exe","bin\sellItem.exe")

$gccCommand = "gcc"
$gccArgs = "-o"

for ($i = 0; $i -lt $sourceFiles.Count; $i++) {
    $sourceFile = $sourceFiles[$i]
    $outputFile = $outputFiles[$i]
    
    $args = $gccArgs, $outputFile, $sourceFile
    
    Start-Process -NoNewWindow -FilePath $gccCommand -ArgumentList $args -Wait
    
    if (Test-Path $outputFile) {
        Write-Host "Compilation successful. Executable file created: $outputFile"
    } else {
        Write-Host "Compilation failed for file: $sourceFile"
    }
}
