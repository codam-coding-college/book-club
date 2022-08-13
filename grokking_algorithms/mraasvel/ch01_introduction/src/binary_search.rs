use std::cmp::Ordering;

/// Return Some(index) of target in table if present, otherwise None is returned.
///
/// Search space is divided by 2 on each iteration.
/// Meaning this is O(log n) time complexity.
pub fn binary_search<T, U>(table: &[T], target: &U) -> Option<usize>
where
    T: PartialOrd<U>,
{
	binary_search_where(table, |x| {
		if *x < *target {
			Ordering::Less
		} else if *x > *target {
			Ordering::Greater
		} else {
			Ordering::Equal
		}
	})
}


pub fn binary_search_where<T, F>(table: &[T], check: F) -> Option<usize>
where
	F: Fn(&T) -> Ordering
{
    let mut start = 0;
    let mut end = table.len();
    while start < end {
        let index = (start + end) / 2;
		match check(&table[index]) {
			Ordering::Less => start = index + 1,
			Ordering::Greater => end = index,
			Ordering::Equal => return Some(index),
		}
    }
    None
}

/// Returns index of target in table if present, otherwise index of insertion position.
pub fn binary_search_with_index<T, U>(table: &[T], target: &U) -> usize
where
	T: PartialOrd<U>
{
	binary_search_where_with_index(table, |x| {
		if *x < *target {
			Ordering::Less
		} else if *x > *target {
			Ordering::Greater
		} else {
			Ordering::Equal
		}
	})
}

pub fn binary_search_where_with_index<T, F>(table: &[T], check: F) -> usize
where
	F: Fn(&T) -> Ordering
{
    let mut start = 0;
    let mut end = table.len();
    while start < end {
        let index = (start + end) / 2;
		match check(&table[index]) {
			Ordering::Less => start = index + 1,
			Ordering::Greater => end = index,
			Ordering::Equal => return index,
		}
    }
    start
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_binary_search() {
        let array = [1, 3, 5, 7, 9, 15];
        assert_eq!(binary_search(&array, &3).unwrap(), 1);
        assert_eq!(binary_search(&array, &2), None);
        assert_eq!(binary_search(&array, &16), None);
        assert_eq!(binary_search(&array, &1).unwrap(), 0);
        assert_eq!(binary_search(&array, &15).unwrap(), array.len() - 1);
    }

    #[test]
    fn test_binary_search_index() {
        let array = [1, 3, 5, 7, 9, 15];
        assert_eq!(binary_search_with_index(&array, &3), 1);
        assert_eq!(binary_search_with_index(&array, &2), 1);
        assert_eq!(binary_search_with_index(&array, &-5), 0);
        assert_eq!(binary_search_with_index(&array, &17), array.len());
        assert_eq!(binary_search_with_index(&array, &14), array.len() - 1);
    }
}
