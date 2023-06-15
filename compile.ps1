$sourceFiles = @("checkDatabase.c", "file2.c", "file3.c")
$outputFiles = @("bin\checkDatabase.exe", "output2.exe", "output3.exe")

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
