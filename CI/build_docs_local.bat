echo off

cd "../"

".venv/python/python" -m pip install mkdocs mkdocs-material mkdocs-minify-plugin mkdoxy pymdown-extensions mike
".venv/python/python" -m pip install "mkdocs-material[imaging]"
".venv/python/python" -m pip install "mkdocs-material[recommended]"

call scoop install doxygen

".venv/python/python" -m mkdocs serve 

pause
