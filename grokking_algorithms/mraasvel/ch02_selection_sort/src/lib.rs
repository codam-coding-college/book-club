fn find_smallest<T>(table: &[T]) -> usize
where
    T: Ord,
{
    table
        .iter()
        .enumerate()
        .min_by(|(_, x), (_, y)| x.cmp(y))
        .map(|(index, _)| index)
        .unwrap_or(0)
}

pub fn selection_sort<T>(table: &mut [T])
where
    T: Ord,
{
    if table.is_empty() {
        return;
    }
    for index in 0..table.len() - 1 {
        let smallest = index + find_smallest(&table[index..]);
        table.swap(index, smallest);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn is_sorted<T>(data: &[T]) -> bool
    where
        T: Ord,
    {
        data.windows(2).all(|w| w[0] <= w[1])
    }

    #[test]
    fn test_selection_sort() {
        let mut table = [5, 2, 3, 1, 4];
        selection_sort(&mut table);
        assert!(is_sorted(&table));
    }
}
