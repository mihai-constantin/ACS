package skel;

import static skel.IllnessType.ABDOMINAL_PAIN;
import static skel.IllnessType.ALLERGIC_REACTION;
import static skel.IllnessType.BROKEN_BONES;
import static skel.IllnessType.BURNS;
import static skel.IllnessType.CAR_ACCIDENT;
import static skel.IllnessType.CUTS;
import static skel.IllnessType.FOOD_POISONING;
import static skel.IllnessType.HEART_ATTACK;
import static skel.IllnessType.HEART_DISEASE;
import static skel.IllnessType.HIGH_FEVER;
import static skel.IllnessType.PNEUMONIA;
import static skel.IllnessType.SPORT_INJURIES;
import static skel.IllnessType.STROKE;

import static utils.Severity.ABDOMINAL_PAIN_IMMEDIATE;
import static utils.Severity.ALLERGIC_REACTION_IMMEDIATE;
import static utils.Severity.BROKEN_BONES_IMMEDIATE;
import static utils.Severity.BURS_IMMEDIATE;
import static utils.Severity.CAR_ACCIDENT_IMMEDIATE;
import static utils.Severity.CUTS_IMMEDIATE;
import static utils.Severity.FOOD_POISONING_IMMEDIATE;
import static utils.Severity.HEART_ATTACK_IMMEDIATE;
import static utils.Severity.HEART_DISEASE_IMMEDIATE;
import static utils.Severity.HIGH_FEVER_IMMEDIATE;
import static utils.Severity.PNEUMONIA_IMMEDIATE;
import static utils.Severity.SPORT_INJURIES_IMMEDIATE;
import static utils.Severity.STROKE_IMMEDIATE;

import static utils.Severity.ABDOMINAL_PAIN_URGENT;
import static utils.Severity.ALLERGIC_REACTION_URGENT;
import static utils.Severity.BROKEN_BONES_URGENT;
import static utils.Severity.BURNS_URGENT;
import static utils.Severity.CAR_ACCIDENT_URGENT;
import static utils.Severity.CUTS_URGENT;
import static utils.Severity.HEART_ATTACK_URGENT;
import static utils.Severity.FOOD_POISONING_URGENT;
import static utils.Severity.HEART_DISEASE_URGENT;
import static utils.Severity.HIGH_FEVER_URGENT;
import static utils.Severity.PNEUMONIA_URGENT;
import static utils.Severity.SPORT_INJURIES_URGENT;
import static utils.Severity.STROKE_URGENT;

import static utils.Severity.ABDOMINAL_PAIN_LESS_URGENT;
import static utils.Severity.ALLERGIC_REACTION_LESS_URGENT;
import static utils.Severity.BROKEN_BONES_LESS_URGENT;
import static utils.Severity.BURNS_LESS_URGENT;
import static utils.Severity.CAR_ACCIDENT_LESS_URGENT;
import static utils.Severity.CUTS_LESS_URGENT;
import static utils.Severity.FOOD_POISONING_LESS_URGENT;
import static utils.Severity.HEART_ATTACK_LESS_URGENT;
import static utils.Severity.HEART_DISEASE_LESS_URGENT;
import static utils.Severity.HIGH_FEVER_LESS_URGENT;
import static utils.Severity.PNEUMONIA_LESS_URGENT;
import static utils.Severity.SPORT_INJURIES_LESS_URGENT;
import static utils.Severity.STROKE_LESS_URGENT;


import java.util.HashMap;
import java.util.Map;

/**
 * Estimates the urgency based on the patient's illness and how severe the illness is manifested.
 */
public final class UrgencyEstimator {

    private static UrgencyEstimator instance;
    private Map<Urgency, HashMap<IllnessType, Integer>> algorithm;

    private UrgencyEstimator() {
        algorithm = new HashMap<Urgency, HashMap<IllnessType, Integer>>() {
            {
                put(Urgency.IMMEDIATE,
                        new HashMap<IllnessType, Integer>() {
                            {
                                put(ABDOMINAL_PAIN, ABDOMINAL_PAIN_IMMEDIATE.getValue());
                                put(ALLERGIC_REACTION, ALLERGIC_REACTION_IMMEDIATE.getValue());
                                put(BROKEN_BONES, BROKEN_BONES_IMMEDIATE.getValue());
                                put(BURNS, BURS_IMMEDIATE.getValue());
                                put(CAR_ACCIDENT, CAR_ACCIDENT_IMMEDIATE.getValue());
                                put(CUTS, CUTS_IMMEDIATE.getValue());
                                put(FOOD_POISONING, FOOD_POISONING_IMMEDIATE.getValue());
                                put(HEART_ATTACK, HEART_ATTACK_IMMEDIATE.getValue());
                                put(HEART_DISEASE, HEART_DISEASE_IMMEDIATE.getValue());
                                put(HIGH_FEVER, HIGH_FEVER_IMMEDIATE.getValue());
                                put(PNEUMONIA, PNEUMONIA_IMMEDIATE.getValue());
                                put(SPORT_INJURIES, SPORT_INJURIES_IMMEDIATE.getValue());
                                put(STROKE, STROKE_IMMEDIATE.getValue());

                            }
                        });

                put(Urgency.URGENT,
                        new HashMap<IllnessType, Integer>() {
                            {
                                put(ABDOMINAL_PAIN, ABDOMINAL_PAIN_URGENT.getValue());
                                put(ALLERGIC_REACTION, ALLERGIC_REACTION_URGENT.getValue());
                                put(BROKEN_BONES, BROKEN_BONES_URGENT.getValue());
                                put(BURNS, BURNS_URGENT.getValue());
                                put(CAR_ACCIDENT, CAR_ACCIDENT_URGENT.getValue());
                                put(CUTS, CUTS_URGENT.getValue());
                                put(HEART_ATTACK, HEART_ATTACK_URGENT.getValue());
                                put(FOOD_POISONING, FOOD_POISONING_URGENT.getValue());
                                put(HEART_DISEASE, HEART_DISEASE_URGENT.getValue());
                                put(HIGH_FEVER, HIGH_FEVER_URGENT.getValue());
                                put(PNEUMONIA, PNEUMONIA_URGENT.getValue());
                                put(SPORT_INJURIES, SPORT_INJURIES_URGENT.getValue());
                                put(STROKE, STROKE_URGENT.getValue());
                            }
                        });

                put(Urgency.LESS_URGENT,
                        new HashMap<IllnessType, Integer>() {
                            {
                                put(ABDOMINAL_PAIN, ABDOMINAL_PAIN_LESS_URGENT.getValue());
                                put(ALLERGIC_REACTION, ALLERGIC_REACTION_LESS_URGENT.getValue());
                                put(BROKEN_BONES, BROKEN_BONES_LESS_URGENT.getValue());
                                put(BURNS, BURNS_LESS_URGENT.getValue());
                                put(CAR_ACCIDENT, CAR_ACCIDENT_LESS_URGENT.getValue());
                                put(CUTS, CUTS_LESS_URGENT.getValue());
                                put(FOOD_POISONING, FOOD_POISONING_LESS_URGENT.getValue());
                                put(HEART_ATTACK, HEART_ATTACK_LESS_URGENT.getValue());
                                put(HEART_DISEASE, HEART_DISEASE_LESS_URGENT.getValue());
                                put(HIGH_FEVER, HIGH_FEVER_LESS_URGENT.getValue());
                                put(PNEUMONIA, PNEUMONIA_LESS_URGENT.getValue());
                                put(SPORT_INJURIES, SPORT_INJURIES_LESS_URGENT.getValue());
                                put(STROKE, STROKE_LESS_URGENT.getValue());
                            }
                        });

            }
        };
    }

    public static UrgencyEstimator getInstance() {
        if (instance == null) {
            instance = new UrgencyEstimator();
        }
        return instance;
    }

    //called by doctors and nurses
    public Urgency estimateUrgency(IllnessType illnessType, int severity) {

        if (severity >= algorithm.get(Urgency.IMMEDIATE).get(illnessType)) {
            return Urgency.IMMEDIATE;
        }
        if (severity >= algorithm.get(Urgency.URGENT).get(illnessType)) {
            return Urgency.URGENT;
        }
        if (severity >= algorithm.get(Urgency.LESS_URGENT).get(illnessType)) {
            return Urgency.LESS_URGENT;
        }
        return Urgency.NON_URGENT;
    }
}
