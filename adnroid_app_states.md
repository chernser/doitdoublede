Application real state transitions 
==================================


+++ Just opened 
```
2019-05-12 10:28:03.972 23074-23074/? I/om.doitdoubled: Late-enabling -Xcheck:jni
2019-05-12 10:28:04.123 23074-23074/com.doitdoublede W/System: ClassLoader referenced unknown path: 
2019-05-12 10:28:04.139 23074-23074/com.doitdoublede I/Perf: Connecting to perf service.
2019-05-12 10:28:04.215 23074-23074/com.doitdoublede D/OpenGLRenderer: Skia GL Pipeline
2019-05-12 10:28:04.245 23074-23094/com.doitdoublede I/engine: Android main 
2019-05-12 10:28:04.261 23074-23094/com.doitdoublede D/engine: lifecycle: Resumed
2019-05-12 10:28:04.291 23074-23094/com.doitdoublede D/engine: lifecycle: init window
2019-05-12 10:28:04.303 23074-23094/com.doitdoublede D/engine: lifecycle: Gained focus
```

+++ Pressed three dash button 
```
2019-05-12 10:28:20.800 23074-23094/com.doitdoublede D/engine: lifecycle: Paused
2019-05-12 10:28:20.809 23074-23094/com.doitdoublede D/engine: lifecycle: Lost focus
2019-05-12 10:28:20.813 23074-23094/com.doitdoublede I/app: Saving state
2019-05-12 10:28:20.813 23074-23094/com.doitdoublede D/engine: lifecycle: init window <--- this seems preview window 
```

+++ Pressed on application 
```
2019-05-12 10:28:35.882 23074-23094/com.doitdoublede D/engine: lifecycle: Resumed
2019-05-12 10:28:35.895 23074-23094/com.doitdoublede D/engine: lifecycle: Terminate window <---- seems terminating preview window
2019-05-12 10:28:35.895 23074-23094/com.doitdoublede D/engine: lifecycle: init window		<--- initializing main window 
2019-05-12 10:28:35.897 23074-23094/com.doitdoublede D/engine: lifecycle: Gained focus		<--- got focus 
```

+++ Pressed home button
```
2019-05-12 10:28:57.151 23074-23094/com.doitdoublede D/engine: lifecycle: Paused
2019-05-12 10:28:57.165 23074-23094/com.doitdoublede D/engine: lifecycle: Lost focus
2019-05-12 10:28:57.168 23074-23094/com.doitdoublede I/app: Saving state
2019-05-12 10:28:57.168 23074-23094/com.doitdoublede D/engine: lifecycle: init window  <--- preview window ?? 
```

+++ Pressed three dash button and closed application 
```
 					<-------------  no preview window init 
2019-05-12 10:29:16.979 23074-23094/com.doitdoublede D/engine: lifecycle: Terminate window <----- terminating preview window ?
2019-05-12 10:29:16.980 23074-23094/com.doitdoublede D/engine: lifecycle: Destroy <----- destroying application 
```
