CPP_FILES="io.cpp sortings.cpp main.cpp"
APP=shall_sort

if [ -f $APP ]; then rm $APP
fi

g++ $CPP_FILES -o $APP

./$APP