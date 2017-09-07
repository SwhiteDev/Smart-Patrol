DIR="/home/swhite/Smart-Patrol"

$DIR/camera/camera --count 1

sleep 1

curl -F "image=@test.jpeg" "http://www.jiangh.me/Xungeng/admin/uploadImage"
