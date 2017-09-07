DIR="/home/swhite/Smart-Patrol"

$DIR/camera/camera --count 1

rm $DIR/camera/test.yuv

sleep 1

curl -F "image=@test.jpeg" "http://www.jiangh.me/Xungeng/admin/uploadImage"
