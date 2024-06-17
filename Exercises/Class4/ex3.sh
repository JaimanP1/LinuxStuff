#!/bin/bash

ranks=(2 3 4 5 6 7 8 9 10 Jack Queen King Ace)
suits=(Clubs Spades Diamonds Hearts)

ranks_num=${ranks[*]}
suits_num=${suits[@]}

random_ranks=$((RANDOM%ranks_num))
random_suits=$((RANDOM%suits_num))

echo "${ranks[random_rank]} of ${suits[random_suits]}"
