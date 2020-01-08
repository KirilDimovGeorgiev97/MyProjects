To successfully compile and build the project you will now also need the assimp library (http://www.assimp.org/index.php).
You can install an older version of the assimp library as a NuGet package - look for assimp.v140. 
The reference docs for the assimp library can be found at http://sir-kimmi.de/assimp/lib_html/index.html. 
Take a look at the Usage and Data Structures topics (http://sir-kimmi.de/assimp/lib_html/usage.html,
 http://sir-kimmi.de/assimp/lib_html/data.html) for a short overview. The Classes topic contains the reference for the Assimp classes.

Tasks:
- Try loading into the application a second model from another file.
- Currently the Model class can be used for loading from single model files, i.e. it doesnt load model transformations.
 How can you change that?