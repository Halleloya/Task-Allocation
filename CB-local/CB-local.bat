set p=0.9
set deviceNum=100
set sampleNum=5

for /L %%j in (1,1,%sampleNum%) do bin\Debug\CB-local ..\Sample\sample%p%_%deviceNum%\sample%p%_%deviceNum%_%%j.in  Result%p%_%deviceNum%.out
pause