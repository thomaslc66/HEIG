/**
 -----------------------------------------------------------------------------------
 File        : Cours.java
 Author(s)   : Michaël Brouchoud
 Date        : 04.12.2017

 Purpose     : Cours represent a Cours

 Note(s)     : -

 -----------------------------------------------------------------------------------
 */

import org.hibernate.Session;
import org.hibernate.annotations.Any;
import org.hibernate.annotations.AnyMetaDef;
import org.hibernate.annotations.MetaValue;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@Entity
@Table (name="cours")
@Inheritance(strategy = InheritanceType.JOINED)
public class Cours {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    @Column
    private String titre;

    @Column
    private int credits;

    @OneToMany(targetEntity=Inscription.class, fetch = FetchType.LAZY,
            cascade=CascadeType.ALL, mappedBy="cours", orphanRemoval = true)
    private Set<Inscription> inscriptions = new HashSet<Inscription>();

    @Transient
    private Set<Etudiant> etudiants = new HashSet<Etudiant>();

    @Any(metaColumn = @Column(name = "enseignant_type"))
    @AnyMetaDef(idType = "int", metaType = "string",
            metaValues = {
                    @MetaValue(targetEntity = Professeur.class, value = "PROFESSEUR"),
                    @MetaValue(targetEntity = ChargeDeCours.class, value = "CHARGEDECOURS"),
            })
    @JoinColumn(name="enseignant_id")
    private Enseignant enseignant;

    public Cours() {}

    public Cours(String titre, int credits) {
        this.titre = titre;
        this.credits = credits;
    }

    public Cours(String titre) {
        this(titre, 0);
    }

    public int getId() {
        return id;
    }

    private void setId(int id){
        this.id = id;
    }

    public String getTitre() {
        return titre;
    }

    public void setTitre(String titre) {
        this.titre = titre;
    }

    public int getCredits() {
        return credits;
    }

    public void setCredits(int credits) {
        this.credits = credits;
    }

    public Set<Inscription> getInscriptions() {
        return inscriptions;
    }

    public void setInscriptions(Set<Inscription> inscriptions) {
        this.inscriptions = inscriptions;
    }

    public Set<Etudiant> getEtudiants() {
        etudiants.clear();
        for(Inscription inscription : inscriptions) {
            etudiants.add(inscription.getEtudiant());
        }
        return etudiants;
    }

    public boolean equals(Cours cours) {
        return this.id == cours.id;
    }

    public List<Etudiant> etudiantsEnAttente(Session session) {
        List<Object[]> querry = session.createQuery("from Cours as c join c.inscriptions as i join i.etudiant as e where i.grade = '\u0000' and c.id = " + this.id).list();

        ArrayList<Etudiant> coursNonCredit = new ArrayList<Etudiant>();

        for (Object[] o : querry) {
            coursNonCredit.add((Etudiant)o[2]);
        }

        return coursNonCredit;
    }

    public Enseignant getEnseignant() {
        return enseignant;
    }

    public void setEnseignant(Enseignant enseignant) {
        this.enseignant = enseignant;
    }

    @Override
    public String toString() {
        return "Caractéristiques : Cours Normal, " + this.getEnseignant();
    }
}
