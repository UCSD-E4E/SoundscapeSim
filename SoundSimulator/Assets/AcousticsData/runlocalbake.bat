docker run --rm -w /acoustics/ -v "%CD%":/acoustics/working/ mcr.microsoft.com/acoustics/baketools:2022.1.Linux ./tools/Triton.LocalProcessor --configfile Acoustics_BirdDemo_config.xml --workingdir working
del *.enc
echo %DATE% %TIME%
