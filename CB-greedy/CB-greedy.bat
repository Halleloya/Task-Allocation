set p=0.9
set n=100
set sampleNum=5

for /l %%j in (1,1,%sampleNum%) do bin\Debug\CB-greedy  ..\Sample\sample%p%_%n%\sample%p%_%n%_%%j.in   Result%p%_%n%.out
pause