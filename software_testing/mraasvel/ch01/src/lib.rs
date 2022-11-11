use fake::{Fake, Dummy};

#[derive(Debug, PartialEq, Dummy, Clone)]
pub struct Developer {
    name: String,
    #[dummy(faker = "1..10")]
    estimate: u32,
}

/// invariant: developers is a non-empty array
/// returns (minimum, maximum) estimate
/// returns None if every developer has the same estimate
pub fn identify_extremes(developers: &[Developer]) -> Option<(&Developer, &Developer)> {
    debug_assert!(!developers.is_empty());
    let mut min = &developers[0];
    let mut max = &developers[0];
    for dev in developers.into_iter().skip(1) {
        if dev.estimate < min.estimate {
            min = dev
        }
        if dev.estimate > max.estimate {
            max = dev
        }
    }
    if min.estimate == max.estimate {
        None
    } else {
        Some((min, max))
    }
}

#[cfg(test)]
mod tests {
    use fake::Faker;
    use quickcheck::Gen;
    use rand::{seq::SliceRandom, rngs::StdRng, SeedableRng};

    use super::*;

    #[test]
    #[should_panic]
    fn empty() {
        identify_extremes(&[]);
    }

    #[test]
    fn single() {
        let dev = Developer {
            name: "Maarten".to_string(),
            estimate: 0,
        };
        let devs = [dev];
        let result = identify_extremes(&devs);
        assert_eq!(result, None);
    }

    #[test]
    fn longer() {
        let devs = [
            Developer {
                name: "Developer".to_string(),
                estimate: 5,
            },
            Developer {
                name: "Maarten".to_string(),
                estimate: 0,
            },
            Developer {
                name: "Benjamin".to_string(),
                estimate: 7,
            },
        ];
        let (min, max) = identify_extremes(&devs).unwrap();
        assert_eq!(min, &devs[1]);
        assert_eq!(max, &devs[2]);
    }

    #[test]
    fn same_estimates() {
        let devs = [
            Developer {
                name: "Developer".to_string(),
                estimate: 5,
            },
            Developer {
                name: "Maarten".to_string(),
                estimate: 5,
            },
            Developer {
                name: "Benjamin".to_string(),
                estimate: 5,
            },
        ];
        assert_eq!(None, identify_extremes(&devs));
    }


    /*
    Property based tests
    Random inputs are generated using the `fake-rs` crate
    Property based tests are done using the `quickcheck` crate
     */

    #[derive(Debug, Clone)]
    struct ValidExtremesInput(Vec<Developer>);

    impl quickcheck::Arbitrary for ValidExtremesInput {
        fn arbitrary(g: &mut Gen) -> Self {
            let mut rng = StdRng::seed_from_u64(u64::arbitrary(g));
            let mut devs: Vec<Developer> = (0..8).map(|_| Faker.fake_with_rng(&mut rng)).collect();
            devs.extend([
                Developer {
                    name: "Maarten".to_string(),
                    estimate: 0,
                },
                Developer {
                    name: "Diego".to_string(),
                    estimate: 10,
                }
            ].into_iter());
            devs.shuffle(&mut rng);
            ValidExtremesInput(devs)
        }
    }

    #[quickcheck_macros::quickcheck]
    fn property_based(devs: ValidExtremesInput) -> bool {
        let (min, max) = identify_extremes(&devs.0).unwrap();
        min.estimate == 0 && max.estimate == 10
    }
}
