import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Main {
    private static SessionFactory sessionFactory;
    private static Session session;

    private static ArrayList<Cours> cours  = new ArrayList<Cours>();
    private static ArrayList<Etudiant> etudiants = new ArrayList<Etudiant>();
    private static ArrayList<Enseignant> enseignants = new ArrayList<Enseignant>();

    public static void main(String[] args) {
        sessionFactory = new Configuration().configure().buildSessionFactory();
        fillArrays();
        fillDatabase();
        showDatabaseEntry();

        session = sessionFactory.openSession();
        Etudiant etudiant = etudiants.get(2);
        session.flush();
        System.out.println("------------------------------------ Suppression de l'etudiant " + etudiant.getPrenom() + " " + etudiant.getNom() + " ------------------------------------");
        deleteElement(etudiant);
        etudiants.remove(etudiant);
        session.close();
        showDatabaseEntry();

        session = sessionFactory.openSession();
        Cours c = session.load(Cours.class, cours.get(3).getId());
        session.flush();
        System.out.println("------------------------------------ Suppression du cours " + c.getTitre() + " ------------------------------------");
        deleteElement(c);
        cours.remove(c);
        session.close();
        showDatabaseEntry();

        System.out.println("------------------------------------ Attribution de grades ------------------------------------");
        session = sessionFactory.openSession();
        setGrade();
        session.close();

        etudiant = etudiants.get(1);
        System.out.println("------------------------------------ Affichage des cours non notes de l'etudiant " + etudiant.getPrenom() + " " + etudiant.getNom() + " ------------------------------------");
        session = sessionFactory.openSession();
        showStudentNoGradeCours(etudiant);
        session.close();

        c = cours.get(5);
        System.out.println("------------------------------------ Affichage des etudiants non notes du cours " + c.getTitre() + " ------------------------------------");
        session = sessionFactory.openSession();
        showCoursNoGradeEtudiant(c);
        session.close();

        System.out.println("------------------------------------ Affichage des enseignants de l'etudiant " + etudiant.getPrenom() + " " + etudiant.getNom() + " ------------------------------------");
        session = sessionFactory.openSession();
        showStudentTeacher(etudiant);
        session.close();

        sessionFactory.close();
    }

    private static void showStudentTeacher(Etudiant etudiant) {
        for(Enseignant enseignant : etudiant.getEnseignants(session)) {
            System.out.println(enseignant);
        }

        System.out.println();
    }

    private static void showCoursNoGradeEtudiant(Cours c) {
        for(Etudiant etudiant : c.etudiantsEnAttente(session)) {
            System.out.println(etudiant.getPrenom() + " " + etudiant.getNom());
        }

        System.out.println();
    }

    private static void showStudentNoGradeCours(Etudiant etudiant) {
        for(Cours c : etudiant.coursNonCredites(session)) {
            System.out.println(c.getTitre());
        }

        System.out.println();
    }

    private static void setGrade() {
        try {
            etudiants.get(0).attribuerGrade(cours.get(0), 'B', session);
            etudiants.get(1).attribuerGrade(cours.get(0), 'C', session);
            etudiants.get(2).attribuerGrade(cours.get(4), 'D', session);
            etudiants.get(3).attribuerGrade(cours.get(5), 'E', session);
            etudiants.get(0).attribuerGrade(cours.get(1), 'F', session);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        System.out.println();
    }

    private static void deleteElement(Object o) {
        Transaction transaction = session.beginTransaction();
        session.delete(o);
        transaction.commit();
    }

    private static void fillDatabase() {
        System.out.println("------------------------------------ Remplissage de la base de donnees ------------------------------------");
        session = sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();

        for(Cours c : cours) {
            session.saveOrUpdate(c);
        }

        for(Etudiant etudiant : etudiants) {
            session.saveOrUpdate(etudiant);
        }

        for(Enseignant enseignant : enseignants) {
            session.saveOrUpdate(enseignant);
        }

        transaction.commit();
        session.close();
    }

    private static void showDatabaseEntry() {
        session = sessionFactory.openSession();

        List<Etudiant> etudiantsQuerry = session.createQuery("from Etudiant").list();

        System.out.println("Lise d'etudiants avec la liste de cours pour chaque etudiants");
        for(Etudiant etudiant : etudiantsQuerry) {
            System.out.println(etudiant.getPrenom() + " " + etudiant.getNom());
            for(Cours c : etudiant.getCours()) {
                System.out.println(c.getTitre());
                System.out.println(c);
            }
        }

        System.out.println();

        List<Cours> coursQuerry = session.createQuery("from Cours").list();

        System.out.println("Lise de cours avec la liste d'etudiants pour chaque cours");
        for(Cours c : coursQuerry) {
            System.out.println(c.getTitre());
            System.out.println(c);
            for(Etudiant etudiant : c.getEtudiants()) {
                System.out.println(etudiant.getPrenom() + " " + etudiant.getNom());
            }
        }

        System.out.println();

        session.close();
    }

    public static void fillArrays() {
        cours.clear();
        etudiants.clear();
        enseignants.clear();

        Cours cours1 = new Cours("Cours 1", 60);
        Cours cours2 = new Cours("Cours 2", 50);
        Cours cours3 = new Cours("Cours 3", 70);
        Cours cours4 = new Cours("Cours 4", 20);
        Cours cours5 = new Cours("Cours 5", 30);
        Cours cours6 = new Cours("Cours 6", 40);

        cours.add(cours1);
        cours.add(cours2);
        cours.add(cours3);
        cours.add(cours4);
        cours.add(cours5);
        cours.add(cours6);

        Etudiant etudiant1 = new Etudiant("thomas", "lechaire", LocalDate.of(1988, 5, 12));
        Etudiant etudiant2 = new Etudiant("michael", "brouchoud", LocalDate.of(1990, 1, 19));
        Etudiant etudiant3 = new Etudiant("quentin", "tarantino", LocalDate.of(1978, 4, 25));
        Etudiant etudiant4 = new Etudiant("james", "bond", LocalDate.of(1007, 7, 7));
        Etudiant etudiant5 = new Etudiant("chuck", "norris", LocalDate.of(1448, 6, 2));

        etudiants.add(etudiant1);
        etudiants.add(etudiant2);
        etudiants.add(etudiant3);
        etudiants.add(etudiant4);
        etudiants.add(etudiant5);

        etudiant1.ajouterCours(cours1);
        etudiant1.ajouterCours(cours4);
        etudiant2.ajouterCours(cours1);
        etudiant2.ajouterCours(cours2);
        etudiant2.ajouterCours(cours4);
        etudiant3.ajouterCours(cours3);
        etudiant4.ajouterCours(cours1);
        etudiant4.ajouterCours(cours5);
        etudiant4.ajouterCours(cours6);
        etudiant5.ajouterCours(cours6);

        Professeur professeur1 = new Professeur("Martin", "Pecheur", "MPR");
        Professeur professeur2 = new Professeur("Ludovic", "Magnin", "LMN");

        ChargeDeCours chargeDeCours1 = new ChargeDeCours("Jean-Claude Vendame");
        ChargeDeCours chargeDeCours2 = new ChargeDeCours("Jean-Claude Gus");

        CoursExterieur coursExterieur1 = new CoursExterieur("Cours Exterieur1", 25, "Ecole Exterieur1");
        CoursExterieur coursExterieur2 = new CoursExterieur("Cours Exterieur2", 30, "Ecole Exterieur1");
        CoursExterieur coursExterieur3 = new CoursExterieur("Cours Exterieur3", 30, "Ecole Exterieur2");

        cours1.setEnseignant(professeur1);
        cours2.setEnseignant(chargeDeCours1);
        cours3.setEnseignant(chargeDeCours2);
        cours5.setEnseignant(professeur2);
        cours6.setEnseignant(professeur2);
        coursExterieur1.setEnseignant(professeur1);
        coursExterieur2.setEnseignant(professeur2);
        coursExterieur3.setEnseignant(professeur1);

        etudiant1.ajouterCours(coursExterieur1);
        etudiant1.ajouterCours(coursExterieur2);
        etudiant1.ajouterCours(coursExterieur3);
        etudiant2.ajouterCours(coursExterieur1);
        etudiant3.ajouterCours(coursExterieur1);
        etudiant4.ajouterCours(coursExterieur2);
        etudiant5.ajouterCours(coursExterieur3);


        enseignants.add(professeur1);
        enseignants.add(professeur2);
        enseignants.add(chargeDeCours1);
        enseignants.add(chargeDeCours2);

        cours.add(coursExterieur1);
        cours.add(coursExterieur2);
        cours.add(coursExterieur3);
    }
}
