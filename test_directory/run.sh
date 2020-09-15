l=1
RED='\033[1;31m'
NC='\033[0m'
clear
while read line; do
  ./reset.sh
  echo -e "${RED}TEST $l:${NC} [$line]"
  (eval $line) &
  ./show.sh
  ((l++))
done < ./other/commands